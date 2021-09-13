#define _POSIX_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "systemfunctions.h"
#include "errors.h"

int main() {
	char str[4096];
	char * palavras[100];
	int npalavras = 0;

	char *token;

	printf("myshell> ");

	while (fgets(str, 256, stdin) != NULL) {
		// Codigo abaixo relativo a separacao de palavra por palavra
		token = strtok(str, " \t\n");
		while (token != NULL) {
			palavras[npalavras] = token;
			npalavras++;
			token = strtok(NULL, " \t\n");
		}
		palavras[npalavras] = 0;

		if (strcmp(palavras[0], "start") == 0) {
			startProcess(palavras, npalavras);
			sleep(1);
		} else if (strcmp(palavras[0], "wait") == 0) {
			waitProcess();
		} else if(strcmp(palavras[0], "kill") == 0) {
			killProcess(atoi(palavras[1]));
			sleep(1);
		} else if (strcmp(palavras[0], "exit") == 0 || strcmp(palavras[0], "quit") == 0) {
			exit(0);
		} else {
			printf("myshell: Comando desconhecido: %s\n", palavras[0]);
		}

		npalavras = 0;
		printf("myshell> ");
	}

	return EXIT_SUCCESS;
}
