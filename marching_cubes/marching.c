#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEBUG 1
#define LUTLINES 256
#define LUTCOLUMN 16

FILE *fl_DEBUG;
int LUT[LUTLINES][LUTCOLUMN];

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
	FILE *fl_input;
	// <DEBUG>
	if (DEBUG == 1){
		printf("[readFile] - Iniciando Função\n");
		fprintf(fl_DEBUG, "[readFile] - Iniciando Função\n");
		fprintf(fl_DEBUG, "[readFile] - Lendo do arquivo: %s\n", argv[1]);
	} // </DEBUG>

	fl_input = fopen(argv[1], "r" );
	if (fl_input == 0) {
        printf("[readFile] - Falar ao tentar abrir: %s\n", argv[1]);
        exit(1);
    }

    for(int i = 0; i < LUTLINES; i++) {
    	for(int j = 0; j < LUTCOLUMN; j++){
    	   	fscanf(fl_input, "%d", &LUT[i][j]);
    	}
    }
    // <DEBUG>
	if (DEBUG == 1){
		for(int i = 0; i < LUTLINES; i++) {
			fprintf(fl_DEBUG, "[readFile] Linha '%d': - ", i+1);
	    	for(int j = 0; j < LUTCOLUMN; j++){
				fprintf(fl_DEBUG, "%d ", LUT[i][j]);
	    	}
	    	fprintf(fl_DEBUG, "\n");
	    }
	} // </DEBUG>

	fscanf(fl_input, "%d", &planSize);

	fclose( fl_input );
	// <DEBUG>
	if (DEBUG == 1){
		printf("[readFile] - Finalizando Função\n");
		fprintf(fl_DEBUG, "[readFile] - Finalizando Função\n");
	} // </DEBUG>
}