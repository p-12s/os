#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <dirent.h>

const char* OS_VERSION_PATH = "/etc/";
const char* VERSION_FILE_POSTFIX = "issue";
const char* RELEASE_FILE_POSTFIX = "release";

const char* TrimParamName(const char* str)
{
	if (strlen(str) == 0)
	{
		return "";
	}

	char* result = strtok((char*)str, "=\"");
	char* nextResult = strtok(NULL, "=\"");

	return (nextResult) ? nextResult : result;
}

const char* ReadFirstLine(const char* fileName)
{
	char* filePath = (char*)malloc(strlen(OS_VERSION_PATH) + strlen(fileName) + 2);
	strcpy(filePath, OS_VERSION_PATH);
	strcat(filePath, (char*)"/");
	strcat(filePath, fileName);

	FILE* fp;
    char* line;
    size_t len = 0;

    fp = fopen(filePath, "r");
	if (fp == NULL)
	{
		return "";
	}

	getline(&line, &len, fp);

    fclose(fp);

    return line;
}

const char* TryToGetOSName(const char* fileName)
{
	char* result = (char*)ReadFirstLine(fileName);

	return TrimParamName(result);
}

int CheckIsPossibleOSInfoFile(const char* fileName)
{
	return strstr(fileName, VERSION_FILE_POSTFIX) != NULL || 
			strstr(fileName, RELEASE_FILE_POSTFIX) != NULL;
}

const char* GetOSName()
{
	DIR* dir;
	struct dirent* ent;
	char* result = (char*)"Unknown";

	dir = opendir(OS_VERSION_PATH);
	if (dir == NULL)
	{
		return result;
	}

	ent = readdir(dir);
	while (ent != NULL)
	{
		if (CheckIsPossibleOSInfoFile(ent->d_name))
		{
			const char* OSName = TryToGetOSName(ent->d_name);
			if (strlen(OSName) != 0)
			{
				result = (char*)OSName;
				break;
			}
		}

		ent = readdir(dir);
	}
	closedir (dir);

	return result;
}

void GetOSInfo()
{
	struct utsname unameData;
	uname(&unameData);

	printf("OS: %s\n", GetOSName());
	printf("Kernel: %s %s\n", unameData.sysname, unameData.release);
	printf("Version: %s\n", unameData.version);
	printf("Arch: %s\n", unameData.machine);
}


int main()
{
	GetOSInfo();
	return 0;
}
