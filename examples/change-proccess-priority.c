#include <windows.h>
#include <tlhelp32.h>
#include <math.h>
#include <stdio.h>  

int main(int argc, char *argv[])
{
	if (!(argv[1] && argv[2]))
	{
		printf("Correct input is - nice-win.exe <processId> <processPriority> \n 1 - ABOVE_NORMAL_PRIORITY_CLASS \n 2 - BELOW_NORMAL_PRIORITY_CLASS \n 3 - HIGH_PRIORITY_CLASS \n 4 - IDLE_PRIORITY_CLASS \n 5 - NORMAL_PRIORITY_CLASS \n 6 - REALTIME_PRIORITY_CLASS");
		exit(EXIT_FAILURE);
	}

	int processID;
	int priorityID;

	processID = atoi(argv[1]);
	priorityID = atoi(argv[2]);

	if (priorityID > 6 || priorityID < 1)
	{
		printf("processPriority from 1 to 6 - \n 1 - ABOVE_NORMAL_PRIORITY_CLASS \n 2 - BELOW_NORMAL_PRIORITY_CLASS \n 3 - HIGH_PRIORITY_CLASS \n 4 - IDLE_PRIORITY_CLASS \n 5 - NORMAL_PRIORITY_CLASS \n 6 - REALTIME_PRIORITY_CLASS");
		exit(EXIT_FAILURE);
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, processID);
	if (hProcess == NULL)
	{
		printf("Unable to get handle of process: %d\n", processID);
		printf("Error is: %d\n", GetLastError());
		return 1;
	}

	printf("Current Priority Class: %d\n", GetPriorityClass(hProcess));

	switch (priorityID)
	{
	case 1:
		SetPriorityClass(hProcess, ABOVE_NORMAL_PRIORITY_CLASS);
		break;

	case 2:
		SetPriorityClass(hProcess, BELOW_NORMAL_PRIORITY_CLASS);
		break;

	case 3:
		SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
		break;

	case 4:
		SetPriorityClass(hProcess, IDLE_PRIORITY_CLASS);
		break;

	case 5:
		SetPriorityClass(hProcess, NORMAL_PRIORITY_CLASS);
		break;

	case 6:
		SetPriorityClass(hProcess, REALTIME_PRIORITY_CLASS);
		break;
	}

	printf("Set to Priority Class: %d\n", GetPriorityClass(hProcess));
	CloseHandle(hProcess);

	exit(EXIT_SUCCESS);
	
}

