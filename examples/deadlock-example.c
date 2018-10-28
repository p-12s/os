#include <stdio.h>
#include <conio.h>

int maximum[100][100];
int allocation[100][100];
int need[100][100];
int available[100];
int dead[100];
int processNumber;
int resources;
int countOfDeadProcess = 0;

void input();
void show();
void calculate();

int main()
{
	input();
	show();
	calculate();	
	return 0;
}

void input()
{
	printf("Enter the number of Processes ");
	scanf_s("%d", &processNumber);

	printf("Enter the number of resource instances ");
	scanf_s("%d", &resources);

	printf("Enter the Max Matrix\n");

	for (int i = 0; i<processNumber; i++)
	{
		for (int j = 0; j<resources; j++)
		{
			scanf_s("%d", &maximum[i][j]);
		}
	}

	printf("Enter the Allocation Matrix\n");

	for (int i = 0; i<processNumber; i++)
	{
		for (int j = 0; j<resources; j++)
		{
			scanf_s("%d", &allocation[i][j]);
		}
	}

	printf("Enter the available Resources\n");

	for (int j = 0; j<resources; j++)
	{
		scanf_s("%d", &available[j]);
	}
}

void show()
{
	printf("Process\t Allocation\t Max\t Available\t");

	for (int i = 0; i<processNumber; i++)
	{
		printf("\nP%d\t   ", i + 1);

		for (int j = 0; j<resources; j++)
		{
			printf("%d ", allocation[i][j]);
		}

		printf("\t");

		for (int j = 0; j<resources; j++)
		{
			printf("%d ", maximum[i][j]);
		}

		printf("\t");

		if (i == 0)
		{
			for (int j = 0; j < resources; j++)
			{
				printf("%d ", available[j]);
			}
		}
	}
}

void calculate()
{
	int finish[100];
	int	need[100][100];
	int deadlockNumber = 0;

	for (int i = 0; i<processNumber; i++)
	{
		finish[i] = 0;
	}

	for (int i = 0; i<processNumber; i++)
	{
		for (int j = 0; j<resources; j++)
		{
			need[i][j] = maximum[i][j] - allocation[i][j];
		}
	}

	for (int i = 0; i<processNumber; i++)
	{
		int c = 0;
		for (int j = 0; j<resources; j++)
		{
			if ((finish[i] == 0) && (need[i][j] <= available[j]))
			{
				c++;
				if (c == resources)
				{
					for (int k = 0; k<resources; k++)
					{
						available[k] += allocation[i][j];
						finish[i] = 1;
					}
				}
			}
		}
	}

	int deadLockFound = 0;

	for (int i = 0; i<processNumber; i++)
	{
		if (finish[i] == 0)
		{
			dead[i] = i + 1;
			deadLockFound = 1;
		}
	}

	if (deadLockFound == 1)
	{
		printf("\n\nSystem is in Deadlock and the Deadlock process are\n");

		for (int i = 0; i<processNumber; i++)
		{
			if (dead[i] > 0)
			{
				printf("P%d\t", dead[i]);
				countOfDeadProcess++;
			}
		}
	}
	else
	{
		printf("\n\nNo Deadlock found");
	}
}