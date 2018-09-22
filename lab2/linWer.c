#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <stdio.h>

static int main_loop(char *pidstatus)
{
	char path[40];
	char *line;
	char *vmname;
	char *vmsize;
	char *vmpeak;
	char *vmrss;
	char *vmhwm;	
	size_t len;	
	FILE *f;

	vmname = NULL;	
	vmsize = NULL;
	vmpeak = NULL;
	vmrss = NULL;
	vmhwm = NULL;
	line = malloc(128);
	len = 128;

	snprintf(path, 40, "/proc/%s/status", pidstatus); 
	
	f = fopen(path, "r");
	if (!f) return 1;
	
	/* Read memory size data from /proc/pid/status */
	while (!vmsize || !vmpeak || !vmrss || !vmhwm)
	{
		if (getline(&line, &len, f) == -1)
		{
			/* Some of the information isn't there, die */
			return 1;
		}

		/* Find VmName */
		if (!strncmp(line, "Name:", 5))
		{
			vmname = strdup(&line[6]);
		}
		
		/* Find VmPeak */
		if (!strncmp(line, "VmPeak:", 7))
		{
			vmpeak = strdup(&line[8]);
		}
		
		/* Find VmSize */
		else if (!strncmp(line, "VmSize:", 7))
		{
			vmsize = strdup(&line[8]);
		}
		
		/* Find VmRSS */
		else if (!strncmp(line, "VmRSS:", 6))
		{
			vmrss = strdup(&line[7]);
		}
		
		/* Find VmHWM */
		else if (!strncmp(line, "VmHWM:", 6))
		{
			vmhwm = strdup(&line[7]);
		}
	}
	free(line);	
	fclose(f);
	
	fprintf(stderr, "pid - %s name - %svmsize - %svmpeak - %svmrss - %svmhwm- %s", pidstatus, vmname, vmsize, vmpeak, vmrss, vmhwm);
	
	free(vmname);
	free(vmpeak);
	free(vmsize);
	free(vmrss);
	free(vmhwm);
	
	return 1;
}

int  print_cmdline( char* proc_id){
	FILE* statusf;
   	char path[40], line[100], *p;

	snprintf(path, 40, "/proc/%s/cmdline", proc_id); 

	statusf = fopen(path, "r");
	if(!statusf)
		return 1;    

	while(fgets(line, 100, statusf)!= NULL) {
		printf("command line - %s", line);
	}

	printf("\n\n");
	fclose(statusf);

	return 1;
}

int  main( int argc, char** argv ){

	DIR *dirp;
	struct dirent *dp;
	int statusResult = 0;
	int cmdlineResult = 0;

	if ((dirp = opendir("/proc")) == NULL) {
		perror("couldn't open '/proc'");
		exit( EXIT_FAILURE );
	}

	while( (dp = readdir(dirp)) != NULL){
		if( dp->d_type == DT_DIR && isdigit( dp->d_name[0] ) ){
			statusResult = main_loop( dp->d_name);
			cmdlineResult = print_cmdline(dp->d_name);

			if( !statusResult && !cmdlineResult ){	
				exit( EXIT_FAILURE );
				closedir(dirp);
			}
		}
	}

	closedir(dirp);
	exit( EXIT_SUCCESS );
}