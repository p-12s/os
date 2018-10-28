#include "windows.h"
#include <process.h>
#include <stdio.h>

void main()
{
	HANDLE mut = CreateMutex(NULL, FALSE, "FirstStep");
	DWORD result = WaitForSingleObject(mut, 0);

	if (result == WAIT_OBJECT_0) 
	{
        printf("programm running\n");
		int i;
        scanf("%d", &i);
		ReleaseMutex(mut);
	}
	else
    {
        printf("fail programm running\n");
    }
    
	CloseHandle(mut);
}