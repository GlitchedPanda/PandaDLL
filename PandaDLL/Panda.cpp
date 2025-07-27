#include "Panda.h"

QXMLDATA procAddr = nullptr;

std::vector<Entitlement*> entitlements = {};

DWORD WINAPI Panda::Attach(LPVOID lpParam)
{
	HMODULE hModule = (HMODULE)lpParam;
	Debug("Attached to EADesktop.exe"); 

	while (!GetModuleHandleW(L"Qt5Core.dll"))
		Sleep(1000);
	Debug("Qt5Core.dll loaded");

	procAddr = (QXMLDATA)GetProcAddrFromDllFunc("Qt5Core.dll", "?data@?$QVector@VQXmlStreamAttribute@@@@QEBAPEBVQXmlStreamAttribute@@XZ");

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	if (procAddr)
	{
		std::stringstream ss;
		ss << "Found dll function: " << procAddr;
		Debug(ss.str().c_str());

		DetourAttach(&(PVOID&)procAddr, Panda::DetourFunction);
		DetourTransactionCommit();
		Debug("Detoured function successfully");

		// Parse the config to get entitlement values
		Panda::LoadEntitlements(); 
	}
	else
	{
		Debug("Could not find hook function");
		DetourTransactionAbort();
	}

	return 0;
}

char* Panda::DetourFunction(void* self)
{
	char* hookFuncResult = procAddr(self);

	if (!hookFuncResult || !strstr(hookFuncResult, "<LSX>"))
		return hookFuncResult;

	char* modifiedResponse = _strdup(hookFuncResult);
	char* hasIsLessThan = (char*)memchr(modifiedResponse, '<', sizeof(modifiedResponse));
	if (!hasIsLessThan)
		return hookFuncResult;
	
	if (!strstr(modifiedResponse, "<Response ") || !strstr(modifiedResponse, "<QueryEntitlementsResponse>"))
		return hookFuncResult;

	// Edit response
	Panda::ModifyResponse(modifiedResponse);

	// Create a thread to free buffer after 1 second
	CreateThread(0, 0, Panda::FreeBuffer, modifiedResponse, 0, 0);

	return modifiedResponse;
}

int Panda::ModifyResponse(char*& buffer)
{
	std::string modifiableString = std::string(_strdup(buffer));

	if (strstr(buffer, "Group=\"\"")) // Ignore this response because we don't want to modify it
	{
		return 1;
	}

	std::string newContent = "<QueryEntitlementsResponse>\n";
	int index = 1;
	for (Entitlement* entitlement : entitlements)
	{
		std::string entitlementString = std::string(entitlement->getEntitlementString(1000000000000 + index).c_str());
		newContent.append(entitlementString + "\n");

		++index;
	}
	newContent.append("</QueryEntitlementsResponse>");

	size_t start = modifiableString.find("<QueryEntitlementsResponse>");
	size_t end = modifiableString.find("</QueryEntitlementsResponse>") + strlen("</QueryEntitlementsResponse>");

	modifiableString.replace(start, end - start, newContent);

	free(buffer);
	buffer = _strdup(modifiableString.c_str());

	return 1;
}

int Panda::LoadEntitlements()
{
	std::string line;

	std::string type;
	std::string entitlementTag;
	std::string itemId;
	std::string group;

	char* appData;
	size_t len = 0;
	_dupenv_s(&appData, &len, "APPDATA");

	std::ifstream entitlementsFile(std::string(appData) + "\\GlitchedPanda\\EA DLC Unlocker V1\\entitlements.ini");
	if (!entitlementsFile.is_open())
	{
		Debug("Could not load entitlements file");
		return 0;
	}

	while (std::getline(entitlementsFile, line))
	{
		// Remove trailing or ending whitespace
		line.erase(0, line.find_first_not_of(" \t"));
		line.erase(line.find_last_not_of(" \t") + 1);

		if (line.starts_with("[") && line.ends_with("]")) // [Pretty Name]
		{
			// Save previous values if there is one
			if (!itemId.empty())
			{
				Entitlement* entitlement = new Entitlement(type, entitlementTag, itemId, group);
				entitlements.push_back(entitlement);
			}

			// Reset values when new section is found
			type = "";
			entitlementTag = "";
			itemId = "";
			group = "";
		}

		if (line.starts_with("IID=")) // IID=SIMS4.OFF.SOLP.0x0000000000000000
		{
			line.erase(0, 4);
			itemId = line.c_str();
		}

		if (line.starts_with("ETG=")) // ETG=name_0x0000000000000000:11111
		{
			line.erase(0, 4);
			entitlementTag = line.c_str();
		}

		if (line.starts_with("GRP=")) // GRP=THESIMS4PC
		{
			line.erase(0, 4);
			group = line.c_str();
		}

		if (line.starts_with("TYP=")) // TYP=DEFAULT
		{
			line.erase(0, 4);
			type = line.c_str();
		}
	}

	// Save the last value if there is one
	if (!itemId.empty())
	{
		Entitlement* entitlement = new Entitlement(type, entitlementTag, itemId, group);
		entitlements.push_back(entitlement);
	}

	// Close the file when we're done
	entitlementsFile.close();

	Debug(std::string(std::string("Loaded ") + std::to_string(entitlements.size()) + std::string(" entitlements from config")).c_str());

	return 1;
}

DWORD WINAPI Panda::FreeBuffer(LPVOID lpParam)
{
	Sleep(1000);
	free(lpParam);
	return 0;
}

FARPROC Panda::GetProcAddrFromDllFunc(LPCSTR dllName, LPCSTR functionName)
{
	HMODULE hModule = LoadLibraryExA(dllName, 0, 0);
	if (!hModule)
	{
		Debug("Could not load dll");
		return 0;
	}
	FARPROC procAddress = GetProcAddress(hModule, functionName);
	if (!procAddress)
	{
		Debug("Could not load function from dll");
		return 0;
	}

	return procAddress;
}

void Panda::Debug(LPCSTR message)
{
	std::stringstream ss;
	ss << "[Panda] " << message;
	OutputDebugStringA(ss.str().c_str());
}