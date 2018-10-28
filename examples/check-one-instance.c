#include "windows.h"
#include <stdio.h>

BOOL CheckOneInstance()
{
	HANDLE m_hStartEvent = CreateEventW(NULL, TRUE, FALSE, L"EVENT_NAME_HERE");
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(m_hStartEvent);
		m_hStartEvent = NULL;
		printf("Program already running!\n");
		return FALSE;
	}
		
	getchar();
	return TRUE;
}

int main()
{
	CheckOneInstance();
    return 0;
}