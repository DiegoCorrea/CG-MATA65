#include <stdlib.h>
#include <string.h>
#include <stdio.h>
# define DEBUG 1
FILE *fl_DEBUG;

void readFile(int argc, char *argv[]);

int main(int argc, char *argv[]) {	
	if (argc < 2){
		printf("Para executar é necessario um arquivo de entrada\n");
		printf("O Marching Cubes será fechado!\n");
		return 1;
	}

	fl_DEBUG = fopen("marchingDEBUG.log", "w+" );
	// <DEBUG>
	if (DEBUG == 1){
		printf("[main] - Iniciando Programa\n");
		fprintf(fl_DEBUG, "[main] - Iniciando Programa\n");
	} // </DEBUG>


	readFile(argc, argv);


	// <DEBUG>
	if (DEBUG == 1){
		printf("[main] - Finalizando Programa\n");
		fprintf(fl_DEBUG, "[main] - Finalizando Programa\n");
	} // </DEBUG>
	fclose( fl_DEBUG );

	return 0;
}

void readFile(int argc, char *argv[]){
	// <DEBUG>
	if (DEBUG == 1){
		printf("[readFile] - Iniciando Função\n");
		fprintf(fl_DEBUG, "[readFile] - Iniciando Função\n");
		fprintf(fl_DEBUG, "[readFile] - Lendo do arquivo: %s\n", argv[1]);
	} // </DEBUG>


	// <DEBUG>
	if (DEBUG == 1){
		printf("[readFile] - Finalizando Função\n");
		fprintf(fl_DEBUG, "[readFile] - Finalizando Função\n");
	} // </DEBUG>
}