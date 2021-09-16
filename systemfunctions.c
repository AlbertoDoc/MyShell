#define _POSIX_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "systemfunctions.h"
#include "errors.h"

void startProcess(char *argv[], int argc) {
	char * args[argc];
	pid_t processId;


	for (int i = 0; i < argc; i++) {
		args[i] = argv[i];
	}
	args[argc] = NULL;

	if ((processId = fork()) == 0) {
		if (execvp(args[1], &args[1]) == -1) {
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
			printf("myshell: processo %d iniciado.\n", processId);
	}	
}

void waitProcess() {
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

			printf("myshell: processo %d finalizou de forma anormal com sinal %d: %s.\n", corpse, status, signalDescription);
		}
	}
	
	if (childrenCount == 0) {
		printf("myshell: não há processos restantes.\n");
	}
}

void killProcess(pid_t pid) {
		int killResult = kill(pid, SIGKILL);

		if (killResult == -1) {
			switch (errno) {
				case EPERM:
					errorPermission();
					break;
				case ESRCH:
					errorPidNotExist();
					break;
			}
		} else if (killResult == 0) {
			printf("myshell: processo %d foi finalizado.\n", pid);
		}
}


void stopProcess(pid_t pid){
	int stoppingProcess = kill(pid, SIGSTOP);
	if (stoppingProcess == -1) {
			switch (errno) {
				case EPERM:
					errorPermission();
					break;
				case ESRCH:
					errorPidNotExist();
					break;
			}
		} else if (stoppingProcess == 0) {
			printf("myshell: processo %d parou a execução.\n", pid);
		}
}

void continueProcess(pid_t pid){
	int continueProcess = kill(pid, SIGCONT);
	if (continueProcess == -1) {
			switch (errno) {
				case EPERM:
					errorPermission();
					break;
				case ESRCH:
					errorPidNotExist();
					break;
			}
		} else if (continueProcess == 0) {
			printf("myshell: processo %d voltou a execução.\n", pid);
		}
}

void runProcess(char *argv[], int argc){
	char * args[argc];
	pid_t processId;


	for (int i = 0; i < argc; i++) {
		args[i] = argv[i];
	}
	args[argc] = NULL;

	if ((processId = fork()) == 0) {
		if (execvp(args[1], &args[1]) == -1) {
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
		int corpse;
		int status;
		int childrenCount = 0;

		while ((corpse = waitpid(processId, &status, 0)) > 0) {
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
}
