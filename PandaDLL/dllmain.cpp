#include "Panda.h"

WCHAR processName[264];
HMODULE originalDll;

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  reason, LPVOID lpReserved )
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        // attach
        originalDll = LoadLibraryA("C:\\Windows\\System32\\version.dll");
        GetModuleFileNameW(0, processName, sizeof(processName));
        if (wcsstr(processName, L"EADesktop.exe"))
        {
            CreateThread(0, 0, Panda::attach, (LPVOID)hModule, 0, 0);
        }
    } 
    else if (reason == DLL_PROCESS_DETACH)
    {
        // detach
        Panda::detach();
        FreeLibrary(originalDll);
    }

    return TRUE;
}

#pragma region RealDllExports

typedef BOOL(__stdcall* GETFILEVERSIONINFOA)(LPCSTR, DWORD, DWORD, LPVOID);
BOOL APIENTRY GetFileVersionInfoA(LPCSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
#pragma EXPORT
    GETFILEVERSIONINFOA origFunc = (GETFILEVERSIONINFOA)GetProcAddress(originalDll, "GetFileVersionInfoA");
    return origFunc(lptstrFilename, dwHandle, dwLen, lpData);
}

typedef BOOL(__stdcall* GETFILEVERSIONINFOEXA)(DWORD, LPCSTR, DWORD, DWORD, LPVOID);
BOOL APIENTRY GetFileVersionInfoExA(DWORD dwFlags, LPCSTR lpwstrFilename, DWORD  dwHandle, DWORD  dwLen, LPVOID lpData)
{
#pragma EXPORT
    GETFILEVERSIONINFOEXA origFunc = (GETFILEVERSIONINFOEXA)GetProcAddress(originalDll, "GetFileVersionInfoExA");
    return origFunc(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
}

typedef BOOL(__stdcall* GETFILEVERSIONINFOEXW)(DWORD, LPCWSTR, DWORD, DWORD, LPVOID);
BOOL APIENTRY GetFileVersionInfoExW(DWORD dwFlags, LPCWSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
#pragma EXPORT
    GETFILEVERSIONINFOEXW origFunc = (GETFILEVERSIONINFOEXW)GetProcAddress(originalDll, "GetFileVersionInfoExW");
    return origFunc(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
}

typedef DWORD(__stdcall* GETFILEVERSIONINFOSIZEA)(LPCSTR, LPDWORD);
DWORD APIENTRY GetFileVersionInfoSizeA(LPCSTR lptstrFilename, LPDWORD lpdwHandle)
{
#pragma EXPORT
    GETFILEVERSIONINFOSIZEA origFunc = (GETFILEVERSIONINFOSIZEA)GetProcAddress(originalDll, "GetFileVersionInfoSizeA");
    return origFunc(lptstrFilename, lpdwHandle);
}

typedef DWORD(__stdcall* GETFILEVERSIONINFOSIZEEXA)(DWORD, LPCSTR, LPDWORD);
DWORD APIENTRY GetFileVersionInfoSizeExA(DWORD dwFlags, LPCSTR lptstrFilename, LPDWORD lpdwHandle)
{
#pragma EXPORT
    GETFILEVERSIONINFOSIZEEXA origFunc = (GETFILEVERSIONINFOSIZEEXA)GetProcAddress(originalDll, "GetFileVersionInfoSizeExA");
    return origFunc(dwFlags, lptstrFilename, lpdwHandle);
}

typedef DWORD(__stdcall* GETFILEVERSIONINFOSIZEEXW)(DWORD, LPCWSTR, LPDWORD);
DWORD APIENTRY GetFileVersionInfoSizeExW(DWORD dwFlags, LPCWSTR lptstrFilename, LPDWORD lpdwHandle)
{
#pragma EXPORT
    GETFILEVERSIONINFOSIZEEXW origFunc = (GETFILEVERSIONINFOSIZEEXW)GetProcAddress(originalDll, "GetFileVersionInfoSizeExW");
    return origFunc(dwFlags, lptstrFilename, lpdwHandle);
}

typedef DWORD(__stdcall* GETFILEVERSIONINFOSIZEW)(LPCWSTR, LPDWORD);
DWORD APIENTRY GetFileVersionInfoSizeW(LPCWSTR lptstrFilename, LPDWORD lpdwHandle)
{
#pragma EXPORT
    GETFILEVERSIONINFOSIZEW origFunc = (GETFILEVERSIONINFOSIZEW)GetProcAddress(originalDll, "GetFileVersionInfoSizeW");
    return origFunc(lptstrFilename, lpdwHandle);
}

typedef BOOL(__stdcall* GETFILEVERSIONINFOW)(LPCWSTR, DWORD, DWORD, LPVOID);
BOOL APIENTRY GetFileVersionInfoW(LPCWSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
#pragma EXPORT
    GETFILEVERSIONINFOW origFunc = (GETFILEVERSIONINFOW)GetProcAddress(originalDll, "GetFileVersionInfoW");
    return origFunc(lptstrFilename, dwHandle, dwLen, lpData);
}

typedef HANDLE(__stdcall* VERFINDFILEA)(DWORD, LPCSTR, LPCSTR, LPCSTR, LPVOID);
HANDLE APIENTRY VerFindFileA(DWORD uFlags, LPCSTR szFileName, LPCSTR szWinDir, LPCSTR szAppDir, LPVOID lpCurDir)
{
#pragma EXPORT
    VERFINDFILEA origFunc = (VERFINDFILEA)GetProcAddress(originalDll, "VerFindFileA");
    return origFunc(uFlags, szFileName, szWinDir, szAppDir, lpCurDir);
}

typedef HANDLE(__stdcall* VERFINDFILEW)(DWORD, LPCWSTR, LPCWSTR, LPCWSTR, LPVOID);
HANDLE APIENTRY VerFindFileW(DWORD uFlags, LPCWSTR szFileName, LPCWSTR szWinDir, LPCWSTR szAppDir, LPVOID lpCurDir)
{
#pragma EXPORT
    VERFINDFILEW origFunc = (VERFINDFILEW)GetProcAddress(originalDll, "VerFindFileW");
    return origFunc(uFlags, szFileName, szWinDir, szAppDir, lpCurDir);
}

typedef DWORD(__stdcall* VERINSTALLFILEA)(DWORD, LPCSTR, LPCSTR, LPCSTR, LPCSTR);
DWORD APIENTRY VerInstallFileA(DWORD uFlags, LPCSTR szSrcFileName, LPCSTR szDestFileName, LPCSTR szSrcDir, LPCSTR szDestDir)
{
#pragma EXPORT
    VERINSTALLFILEA origFunc = (VERINSTALLFILEA)GetProcAddress(originalDll, "VerInstallFileA");
    return origFunc(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir);
}

typedef DWORD(__stdcall* VERINSTALLFILEW)(DWORD, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR);
DWORD APIENTRY VerInstallFileW(DWORD uFlags, LPCWSTR szSrcFileName, LPCWSTR szDestFileName, LPCWSTR szSrcDir, LPCWSTR szDestDir)
{
#pragma EXPORT
    VERINSTALLFILEW origFunc = (VERINSTALLFILEW)GetProcAddress(originalDll, "VerInstallFileW");
    return origFunc(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir);
}

typedef DWORD(__stdcall* VERLANGUAGENAMEA)(DWORD, LPCSTR, LPVOID, DWORD);
DWORD APIENTRY VerLanguageNameA(DWORD wLang, LPCSTR szLang, LPVOID lpBuffer, DWORD cchBuffer)
{
#pragma EXPORT
    VERLANGUAGENAMEA origFunc = (VERLANGUAGENAMEA)GetProcAddress(originalDll, "VerLanguageNameA");
    return origFunc(wLang, szLang, lpBuffer, cchBuffer);
}

typedef DWORD(__stdcall* VERLANGUAGENAMEW)(DWORD, LPCWSTR, LPVOID, DWORD);
DWORD APIENTRY VerLanguageNameW(DWORD wLang, LPCWSTR szLang, LPVOID lpBuffer, DWORD cchBuffer)
{
#pragma EXPORT
    VERLANGUAGENAMEW origFunc = (VERLANGUAGENAMEW)GetProcAddress(originalDll, "VerLanguageNameW");
    return origFunc(wLang, szLang, lpBuffer, cchBuffer);
}

typedef DWORD(__stdcall* VERQUERYVALUEA)(LPCSTR, LPCSTR, LPVOID*, PUINT);
DWORD APIENTRY VerQueryValueA(LPCSTR pBlock, LPCSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen)
{
#pragma EXPORT
    VERQUERYVALUEA origFunc = (VERQUERYVALUEA)GetProcAddress(originalDll, "VerQueryValueA");
    return origFunc(pBlock, lpSubBlock, lplpBuffer, puLen);
}

typedef DWORD(__stdcall* VERQUERYVALUEW)(LPCWSTR, LPCWSTR, LPVOID*, PUINT);
DWORD APIENTRY VerQueryValueW(LPCWSTR pBlock, LPCWSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen)
{
#pragma EXPORT
    VERQUERYVALUEW origFunc = (VERQUERYVALUEW)GetProcAddress(originalDll, "VerQueryValueW");
    return origFunc(pBlock, lpSubBlock, lplpBuffer, puLen);
}
#pragma endregion