#include<stdio.h>
#include<string.h>

#include "systemfunctions.h"

int main() {
	char str[4096];
	char * palavras[100];
	int npalavras = 0;

	char *token;

	printf("myshell> ");

	while (fgets(str, 256, stdin) != NULL) {

		// Pegando a linha de fgets e colocando em str
		puts(str);

		// Codigo abaixo relativo a separacao de palavra por palavra
		token = strtok(str, " \t\n");
		while (token != NULL) {
			palavras[npalavras] = token;
			npalavras++;
			palavras[npalavras] = 0;

			token = strtok(0, " \t\n");
		}

		if (strcmp(palavras[0], "start") == 0) {
			// TODO Criar funcao para lidar com o comando start
		} else if (strcmp(palavras[0], "wait") == 0) {
			// TODO Criar funcao para lidar com o comando wait
		}

		npalavras = 0;
		printf("myshell> ");
	}

	return 0;
}
