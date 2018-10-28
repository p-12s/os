#include <windows.h>
#include <process.h>
#include <stdio.h>

ITERATIONS_NUMBER = 1000000;
int counter = 0;
HANDLE ghMutex; // дескриптор (число), с помощью которого можно идентифицировать ресурс

unsigned int __stdcall thread1(void* data) // __stdcall используется для вызова функций API Win32
{
	int counter1 = 0;

	for (int i = 0; counter < ITERATIONS_NUMBER; i++) {
		WaitForSingleObject(ghMutex, INFINITE);
		counter++;
		//printf("thread1\n");
		// анлочим ранее залоченный мьютекс
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
		// остановим текущий поток, пока работает тот (хендл которого - ghMutex)
		WaitForSingleObject(ghMutex, INFINITE);
		counter++;
		//printf("thread2\n");
		ReleaseMutex(ghMutex);
		counter2++;
	}
	printf("thread counter2 is %d\n", counter2);
	return 0;
}

int main(int argc, char* argv[])
{
	HANDLE myhandle[2]; // массив дескрипторов ресурсов
	ghMutex = CreateMutex( // создаем дескриптор объекта mutex, если такое имя есть, то получим дескприптор существующего.
		NULL, // атрибут безопасности
		FALSE, // флаг начального владельца
		NULL // имя объекта
	);
	
	// _beginthreadex - создаем новый поток и в случае успешного выполнения операции возвращаем идентификатор потока. 
	// По завершении выполнения поток автоматически завершается
	myhandle[0] = (HANDLE)_beginthreadex(NULL, 0, &thread1, NULL, 0, 0);
	myhandle[1] = (HANDLE)_beginthreadex(NULL, 0, &thread2, NULL, 0, 0);

	// ждет, когда объект, хэндл которого был передан первым аргументом, перейдет в сигнальное состояние
	// второй аргумент - время ожидания в миллисекундах. Если INFINITE - ждать вечно
	WaitForSingleObject(myhandle[0], INFINITE);
	WaitForSingleObject(myhandle[1], INFINITE);

	// в конце дескриптор нужно закрыть
	CloseHandle(myhandle[0]);
	CloseHandle(myhandle[1]);

	printf("common counter is %d\n", counter);



	// ЭТА ПРОГА ВСЕГДА УВЕЛИЧИВАЕТ СЧЕТЧИК НА +1 



	// Semafore/mutex/event

	// 4 потока (thread). 1 читатель + 3 писателя 


	return 0;
}