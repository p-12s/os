#include "windows.h"
#include <process.h>
#include <stdio.h>

BOOL CheckOneInstance()
{
    // создаем дескриптор объекта mutex, если такое имя есть, то получим дескприптор существующего.
	HANDLE m_hStartEvent = CreateEventW(
        NULL, //  атрибуты доступа
        TRUE, // режим сброса события
        FALSE, // начальное состояние
        L"EVENT_NAME_HERE" // имя события
    );

	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(m_hStartEvent);
		m_hStartEvent = NULL;
		printf("Program already running!\n");
		return FALSE;
	}
	
    int i;
    scanf("%d", &i);
	return TRUE;
}

int main()
{
	CheckOneInstance();
    return 0;
}
