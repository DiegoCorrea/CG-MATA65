# include <stdlib.h>
# include <iostream>
# include <vector>
# include <algorithm>

# include <string.h>
# include <stdio.h>
# include <math.h>
using namespace std;

#define DEBUG 1
#define LUTLINES 256
#define LUTCOLUMN 16

FILE *fl_DEBUG;
int LUT[LUTLINES][LUTCOLUMN];
int planSize;
float isoValue;

class Vertex {
  int coordinateX, coordinateY, coordinateZ;
  int status, id;

  public:
    Vertex(int x, int y, int z, int status, int id){
      this->coordinateX = x;
      this->coordinateY = y;
      this->coordinateZ = z;
      this->status = status;
      this->id = id;
    }

    int getCoordinateX(){
      return coordinateX;
    }

    int getCoordinateY(){
      return coordinateY;
    }

    int getCoordinateZ(){
      return coordinateZ;
    }

    int getStatus(){
    	return status;
    }

    int getID(){
    	return id;
    }
};

class Grid {
	vector<Vertex> vertices;

	public:
		Grid(){
			vertices.clear();
		}

		void addVertex(int x, int y, int z, int status) {
			int id = vertices.size();
      Vertex vertex(x, y, z, status, id);
      vertices.push_back(vertex);
    }

    void allVertex() {
    	int size_vertices = vertices.size();

    	for(int i = 0; i < size_vertices; i++){
    		fprintf(fl_DEBUG, "[GRID] ID: %d - (%d, %d, %d) - Status %d\n", vertices[i].getID(),vertices[i].getCoordinateX(), vertices[i].getCoordinateY(), vertices[i].getCoordinateZ(), vertices[i].getStatus());
    	}
    }
};

Grid MarchingGrid;

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
	fprintf(fl_DEBUG, "[readFile] - O tamanho do Plano é: '%d'\n", planSize);
	int v[planSize];
	for(int z = 0; z < planSize; z++){
		for(int y = 0; y < planSize; y++) {
			for (int x = 0; x < planSize; ++x) {
				fscanf(fl_input, "%d", &v[x]);
				fprintf(fl_DEBUG, "%d ", v[x]);
				MarchingGrid.addVertex(x,-y,-z,v[x]);
			}
			fprintf(fl_DEBUG, "\n");
		}
	}

	MarchingGrid.allVertex();

	fscanf(fl_input, "%f", &isoValue);
	fprintf(fl_DEBUG, "[readFile] - O Iso Valor é: %f \n", isoValue);

	fclose( fl_input );
	// <DEBUG>
	if (DEBUG == 1){
		printf("[readFile] - Finalizando Função\n");
		fprintf(fl_DEBUG, "[readFile] - Finalizando Função\n");
	} // </DEBUG>
}


void vertexInterpolation(Vertex origin, Vertex master) {
	float x, y, z, point;


}