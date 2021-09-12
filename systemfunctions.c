#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "systemfunctions.h"

void start(char *argv[], int argc) {
	char * args[argc];
	pid_t processId;


	for (int i = 0; i < argc; i++) {
		args[i] = argv[i];
	}
	args[argc] = NULL;

	if ((processId = fork()) == 0) {
		if (execvp(args[0], args) == -1) {
			switch (errno) {
				case EACESS:
					errorPermission();
					break;
				case ENOMEM:
					errorMemory();
					break;
				case ENOENT:
					errorNotSuchExecutable();
					break;
			}
		}
	} else {
			printf("myshell: processo %d iniciado.\n", processId);
			wait(0);
	}	
}
