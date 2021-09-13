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

	while (1) {
	printf("myshell> ");
	token = fgets(str, 256, stdin);

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
		} else if (strcmp(palavras[0], "exit") == 0 || strcmp(palavras[0], "quit") == 0) {
			exit(0);
		} else if (strcmp(palavras[0], "run") == 0) {
			runProcess(palavras, npalavras);
			sleep(1);
		} else {
			printf("myshell: Comando desconhecido: %s\n", palavras[0]);
		}

		npalavras = 0;
	}

	return EXIT_SUCCESS;
}
