#include <stdlib.h>
#include <stdio.h>

#include "errors.h"

void errorInvalidArguments() {
	printf("Número de argumentos inválidos \n");
	exit(EXIT_FAILURE);
}

void errorPermission() {
	printf("myshell: Permissão negada \n");
	exit(EXIT_FAILURE);
}

void errorMemory() {
	printf("myshell: Sem memória suficiente \n");
	exit(EXIT_FAILURE);
}

void errorNotSuchExecutable() {
	printf("myshell: Executável não existe \n");
	exit(EXIT_FAILURE);
}

void errorPidNotExist() {
	printf("myshell: Esse pid não corresponde a nenhum processo ativo\n");
	exit(EXIT_FAILURE);
}
