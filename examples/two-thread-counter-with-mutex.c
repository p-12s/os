#include <windows.h>
#include <process.h>
#include <stdio.h>

ITERATIONS_NUMBER = 10000;
int counter = 0;
HANDLE ghMutex;


unsigned int __stdcall thread1(void* data)
{
	int counter1 = 0;

	for (int i = 0; counter < ITERATIONS_NUMBER; i++) {
		WaitForSingleObject(ghMutex, INFINITE);
		counter++;
		ReleaseMutex(ghMutex);
		counter1++;
	}
	printf("thread counter1 is %d\n", counter1);
	return 0;
}

unsigned int __stdcall thread2(void* data)
{
	int counter2 = 0;

	for (int i = 0; counter < ITERATIONS_NUMBER; i++) {
		WaitForSingleObject(ghMutex, INFINITE);
		counter++;
		ReleaseMutex(ghMutex);
		counter2++;
	}
	printf("thread counter2 is %d\n", counter2);
	return 0;
}

int main(int argc, char* argv[])
{
	HANDLE myhandle[2];
	ghMutex = CreateMutex(NULL, FALSE, NULL);

	myhandle[0] = (HANDLE)_beginthreadex(NULL, 0, &thread1, NULL, 0, 0);
	myhandle[1] = (HANDLE)_beginthreadex(NULL, 0, &thread2, NULL, 0, 0);
	WaitForSingleObject(myhandle[0], INFINITE);
	WaitForSingleObject(myhandle[1], INFINITE);
	CloseHandle(myhandle[0]);
	CloseHandle(myhandle[1]);
	printf("common counter is %d\n", counter);

	return 0;
}