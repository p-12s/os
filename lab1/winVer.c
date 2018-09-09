#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

void getOSVersion(int argc, wchar_t *argv[])
{
    DWORD dwLevel = 102;
    LPWKSTA_INFO_102 pBuf = NULL;
    NET_API_STATUS nStatus;
    LPWSTR pszServerName = NULL;

    if (argc > 2)
    {
        fwprintf(stderr, L"Usage: %s [\\\\ServerName]\n", argv[0]);
        exit(1);
    }
    // The server is not the default local computer.
    if (argc == 2)
        pszServerName = argv[1];

    // Call the NetWkstaGetInfo function, specifying level 102.
    nStatus = NetWkstaGetInfo(pszServerName, dwLevel, (LPBYTE *)&pBuf);

    //If the call is successful, print the workstation data.
    if (nStatus == NERR_Success)
    {
        printf("Windows OS version:  %d.%d\n", pBuf->wki102_ver_major, pBuf->wki102_ver_minor);

        // QUESTION: // I'm one, but logged on users > 0. Why?
        //printf("# Logged on users: %d\n", pBuf->wki102_logged_on_users);
    }
    else
    {
        fprintf(stderr, "A system error has occurred: %d\n", nStatus);
    }

    // Free the allocated memory.
    if (pBuf != NULL)
        NetApiBufferFree(pBuf);
}

void getBuildVersion()
{
    // WORD и DWORD - unsigned int и unsigned long long для Windows
	DWORD dwVersion = 0;
	DWORD dwBuild = 0;

	dwVersion = GetVersion();
	if (dwVersion < 0x80000000)
		dwBuild = (DWORD)(HIWORD(dwVersion));

	printf("Build version: %d\n", dwBuild);
}

int wmain(int argc, wchar_t *argv[])
{
    getOSVersion(argc, argv);
    getBuildVersion();
    return 0;
}
