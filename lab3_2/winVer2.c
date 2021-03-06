#include <windows.h>
#include <process.h>
#include <stdio.h>

ITERATIONS_NUMBER = 100000;
int counter = 0;
abFlags[1];
int nTurn = 1;

unsigned int __stdcall thread1(void* data)
{
	int counter1 = 0;

	for (int i = 0; counter < ITERATIONS_NUMBER; i++) {
		abFlags[0] = TRUE;
		while (abFlags[1])
			if (nTurn == 1)
			{
				abFlags[0] = FALSE;
				while (nTurn == 1)
					/* пережидание */;
				abFlags[0] = TRUE;
			}
		// критический раздел
		counter++;
		counter1++;

		nTurn = 1;
		abFlags[0] = FALSE;
	}

	printf("thread counter1 is %d\n", counter1);
	return 0;
}

unsigned int __stdcall thread2(void* data)
{
	int counter2 = 0;

	for (int i = 0; counter < ITERATIONS_NUMBER; i++) {
		abFlags[1] = TRUE;
		while (abFlags[0])
			if (nTurn == 0)
			{
				abFlags[1] = FALSE;
				while (nTurn == 0)
					/* пережидание */;
				abFlags[1] = TRUE;
			}
		// критический раздел
		counter++;
		counter2++;

		nTurn = 0;
		abFlags[1] = FALSE;
	}

	printf("thread counter2 is %d\n", counter2);
	return 0;
}

int main(int argc, char* argv[])
{
	HANDLE myhandle[2];
	abFlags[0] = TRUE;
	abFlags[1] = TRUE;

	myhandle[0] = (HANDLE)_beginthreadex(NULL, 0, &thread1, NULL, 0, 0);
	myhandle[1] = (HANDLE)_beginthreadex(NULL, 0, &thread2, NULL, 0, 0);
	WaitForSingleObject(myhandle[0], INFINITE);
	WaitForSingleObject(myhandle[1], INFINITE);
	CloseHandle(myhandle[0]);
	CloseHandle(myhandle[1]);
	printf("common counter is %d\n", counter);

	return 0;
}