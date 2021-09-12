#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "systemfunctions.h"

void startProcess(char *argv[], int argc) {
	char * args[argc];
	pid_t processId;


	for (int i = 0; i < argc; i++) {
		args[i] = argv[i];
	}
	args[argc] = NULL;
	printf("execucao \n");
	if ((processId = fork()) == 0) {
		printf("entrou 1\n");
		if (execvp(args[0], args) == -1) {
			printf("entrou 2\n");
			switch (errno) {
				case EACCES:
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
			printf("entrou 3\n");
			printf("myshell: processo %d iniciado.\n", processId);
			wait(0);
	}	
}

void waitProcess() {
	pid_t processId;

	int corpse;
	int status;
	int childrenCount = 0;

	while ((corpse = waitpid(0, &status, 0)) > 0) {
		childrenCount++;

		if (status == 0) {
			printf("myshell: processo %d finalizou normalmente com status %d.\n", corpse, status);
		} else {
			char * signalDescription;
			switch (status) {
				case 1:
					signalDescription = "SIGHUP";
					break;
				case 2:
					signalDescription = "SIGINT";
					break;
				case 3:
					signalDescription = "SIGQUIT";
					break;
				case 4:
					signalDescription = "SIGILL";
					break;
				case 5:
					signalDescription = "SIGTRAP";
					break;
				case 6:
					signalDescription = "SIGABRT";
					break;
				case 7:
					signalDescription = "SIGEMT";
					break;
				case 8:
					signalDescription = "SIGFPE";
					break;
				case 9:
					signalDescription = "SIGKILL";
					break;
			}

			printf("myshell: processo %d finalizou de formal anormal com sinal %d: %s.\n", corpse, status, signalDescription);
		}
	}
	
	if (childrenCount == 0) {
		printf("myshell: não há processos restantes.\n");
	}
}
