#pragma once

#define WIN32_LEAN_AND_MEAN 
#define EXPORT comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)
#define REGEXPR_NUMBER ^0$|^[1-9][0-9]*$

#include <Windows.h>
#include <detours/detours.h>
#include <shlobj.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

#include <string>
#include <format>

#include <vector>

typedef char* (*QXMLDATA)(void* self);

class Panda
{
public:
	static DWORD WINAPI Attach(LPVOID lpParam);

	static char* DetourFunction(void* self);
	static FARPROC GetProcAddrFromDllFunc(LPCSTR dllName, LPCSTR functionName);
	static DWORD WINAPI FreeBuffer(LPVOID lpParam);

	static int ModifyResponse(char*& buffer);
    static int LoadEntitlements();

	static void Debug(LPCSTR message);
};

class Entitlement
{
private:
    std::string type;
    std::string entitlementTag;
    std::string itemId;
    std::string group;

public:
    
    Entitlement(const std::string& type, const std::string& entitlementTag, const std::string& itemId, const std::string& group)
        : type(type), entitlementTag(entitlementTag), itemId(itemId), group(group)
    {
        // Nothing 
    }

    std::string getEntitlementString(long long entitlementId)
    {
        return std::format
        (
            "<Entitlement Type=\"{}\" GrantDate=\"2010-01-01T00:00:00\" ResourceId=\"\" EntitlementTag=\"{}\" ItemId=\"{}\" Version=\"0\" Expiration=\"0000-00-00T00:00:00\" Group=\"{}\" UseCount=\"0\" LastModifiedDate=\"2010-01-01T00:00:00\" EntitlementId=\"{}\" Source=\"ORIGIN\"/>",
            type, entitlementTag, itemId, group, entitlementId
        );
    }
};