using namespace std;
# include <stdlib.h>
# include <vector>
# include <algorithm>

# include <string.h>
# include <stdio.h>
# include <math.h>

# define DEBUG 1
# define LUTLINES 256
# define LUTCOLUMN 16

FILE *GL_fl_DEBUG;
int LUT[LUTLINES][LUTCOLUMN];
int planSize;
float isoValue;

class Vertex{
  private:
  	int coordinateX, coordinateY, coordinateZ;
  	int status, id;

  public:
    Vertex(int x, int y, int z, int status){
      this->coordinateX = x;
      this->coordinateY = y;
      this->coordinateZ = z;
      this->status = status;
    }
    ~Vertex(){};

    int getCoordinateX(){
      return this->coordinateX;
    }

    int getCoordinateY(){
      return this->coordinateY;
    }

    int getCoordinateZ(){
      return this->coordinateZ;
    }

    int getStatus(){
    	return this->status;
    }

    int getID(){
    	return this->id;
    }
};

vector<vector<vector<Vertex> > > cubeVertices;

// <DEBUG>
void allVertex() {
	for(int x = 0; x < planSize; x++){
		for(int y = 0; y < planSize; y++){
			for(int z = 0; z < planSize; z++){
				fprintf(GL_fl_DEBUG, "[GRID] - (%d, %d, %d) - Status %d\n", cubeVertices[z][y][x].getCoordinateX(), cubeVertices[z][y][x].getCoordinateY(), cubeVertices[z][y][x].getCoordinateZ(), cubeVertices[z][y][x].getStatus());
			}
		}
	}
} // </DEBUG>

void readFile(int argc, char *argv[]);

int main(int argc, char *argv[]){	
	if (argc < 2){
		printf("Para executar é necessario um arquivo de entrada\n");
		printf("O Marching Cubes será fechado!\n");
		return 1;
	}

	GL_fl_DEBUG = fopen("marchingDEBUG.log", "w+" );
	// <DEBUG>
	if (DEBUG == 1){
		printf("[main] - Iniciando Programa\n");
		fprintf(GL_fl_DEBUG, "[main] - Iniciando Programa\n");
	} // </DEBUG>


	readFile(argc, argv);


	// <DEBUG>
	if (DEBUG == 1){
		printf("[main] - Finalizando Programa\n");
		fprintf(GL_fl_DEBUG, "[main] - Finalizando Programa\n");
	} // </DEBUG>
	fclose( GL_fl_DEBUG );

	return 0;
}

void readFile(int argc, char *argv[]){
	FILE *fl_input;
	// <DEBUG>
	if (DEBUG == 1){
		printf("[readFile] - Iniciando Função\n");
		fprintf(GL_fl_DEBUG, "[readFile] - Iniciando Função\n");
		fprintf(GL_fl_DEBUG, "[readFile] - Lendo do arquivo: %s\n", argv[1]);
	} // </DEBUG>

	fl_input = fopen(argv[1], "r" );
	if (fl_input == 0) {
    printf("[readFile] - Falar ao tentar abrir: %s\n", argv[1]);
    exit(1);
  }

  for(int i = 0; i < LUTLINES; i++){
  	for(int j = 0; j < LUTCOLUMN; j++){
  	  fscanf(fl_input, "%d", &LUT[i][j]);
  	}
  }

  // <DEBUG>
	if (DEBUG == 1){
		for(int i = 0; i < LUTLINES; i++) {
			fprintf(GL_fl_DEBUG, "[readFile] Linha '%d': - ", i);
	    for(int j = 0; j < LUTCOLUMN; j++){
				fprintf(GL_fl_DEBUG, "%d ", LUT[i][j]);
	    }
	  	fprintf(GL_fl_DEBUG, "\n");
	  }
	} // </DEBUG>

	fscanf(fl_input, "%d", &planSize);
	int v[planSize][planSize][planSize];

	for(int z = 0; z < planSize; z++){
		vector < vector < Vertex > > d2;
		cubeVertices.push_back( d2 );
		for(int y = 0; y < planSize; y++) {
			vector <Vertex> d3;
      cubeVertices[z].push_back( d3 );
			for (int x = 0; x < planSize; ++x) {
				fscanf(fl_input, "%d", &v[z][y][x]);

				Vertex vertice(x,y,z,v[z][y][x]);
        cubeVertices[z][y].push_back( vertice);
			}
		}
	}
	fscanf(fl_input, "%f", &isoValue);
	// <DEBUG>
	if (DEBUG == 1){
		fprintf(GL_fl_DEBUG, "[readFile] - O tamanho do Plano é: '%d'\n", planSize);
		allVertex();
		fprintf(GL_fl_DEBUG, "[readFile] - O Iso Valor é: %f \n", isoValue);
	} // </DEBUG>

	fclose( fl_input );
	// <DEBUG>
	if (DEBUG == 1){

		printf("[readFile] - Finalizando Função\n");
		fprintf(GL_fl_DEBUG, "[readFile] - Finalizando Função\n");
	} // </DEBUG>
}


void vertexInterpolation(Vertex origin, Vertex master) {
	float x, y, z, point;


}