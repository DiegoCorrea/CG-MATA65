using namespace std;
# include <stdlib.h>
# include <vector>
# include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <iterator>
#include <limits>
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
int convertBinaryToDecimal(long long n);
void readFile(int argc, char *argv[]);
void showCubes();

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
	showCubes();

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
int convertBinaryToDecimal(int n){
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}
int makeBinary(int vec[8]){
	int finalValue = 0;

	finalValue += vec[7]*1;
	finalValue += vec[6]*10;
	finalValue += vec[5]*100;
	finalValue += vec[4]*1000;
	finalValue += vec[3]*10000;
	finalValue += vec[2]*100000;
	finalValue += vec[1]*1000000;
	finalValue += vec[0]*10000000;

	return finalValue;
}
void showCubes(){
	int totalCubes = (planSize-1)*(planSize-1)*(planSize-1);
	int ver[8], config = 0;
	for(int z = 0, cb = 0; z < planSize-1; z++){
		for(int y = 0; y < planSize-1; y++ ) {
			for(int x = 0; x < planSize-1; x++){
				cb += 1;

				ver[0] = cubeVertices[z+1][y+1][x].getStatus();
				ver[1] = cubeVertices[z+1][y+1][x+1].getStatus();
				ver[2] = cubeVertices[z][y+1][x+1].getStatus();
				ver[3] = cubeVertices[z][y+1][x].getStatus();
				ver[4] = cubeVertices[z+1][y][x].getStatus();
				ver[5] = cubeVertices[z+1][y][x+1].getStatus();
				ver[6] = cubeVertices[z][y][x+1].getStatus();
				ver[7] = cubeVertices[z][y][x].getStatus();

				config = convertBinaryToDecimal(makeBinary(ver));

				// <DEBUG>
				if (DEBUG == 1){
					fprintf(GL_fl_DEBUG, "[Cubo %d] - Config number : %d\n", cb,config);
					for(int j = 0; j < LUTCOLUMN; j++){
						fprintf(GL_fl_DEBUG, "%d ", LUT[config][j]);
	    		}
	    		fprintf(GL_fl_DEBUG, "\n");
					fprintf(GL_fl_DEBUG, "Vertice 1: (%d, %d, %d) ou (%d, %d, %d) : status %d\n", x, y, z, cubeVertices[z][y][x].getCoordinateX(), cubeVertices[z][y][x].getCoordinateY(), cubeVertices[z][y][x].getCoordinateZ(), cubeVertices[z][y][x].getStatus());
					fprintf(GL_fl_DEBUG, "Vertice 2: (%d, %d, %d) ou (%d, %d, %d) : status %d\n", x+1, y, z, cubeVertices[z][y][x+1].getCoordinateX(), cubeVertices[z][y][x+1].getCoordinateY(), cubeVertices[z][y][x+1].getCoordinateZ(), cubeVertices[z][y][x+1].getStatus());
					fprintf(GL_fl_DEBUG, "Vertice 3: (%d, %d, %d) ou (%d, %d, %d) : status %d\n", x+1, y, z+1, cubeVertices[z+1][y][x+1].getCoordinateX(), cubeVertices[z+1][y][x+1].getCoordinateY(), cubeVertices[z+1][y][x+1].getCoordinateZ(), cubeVertices[z+1][y][x+1].getStatus());
					fprintf(GL_fl_DEBUG, "Vertice 4: (%d, %d, %d) ou (%d, %d, %d) : status %d\n", x, y, z+1, cubeVertices[z+1][y][x].getCoordinateX(), cubeVertices[z+1][y][x].getCoordinateY(), cubeVertices[z+1][y][x].getCoordinateZ(), cubeVertices[z+1][y][x].getStatus());
					fprintf(GL_fl_DEBUG, "Vertice 5: (%d, %d, %d) ou (%d, %d, %d) : status %d\n", x, y+1, z, cubeVertices[z][y+1][x].getCoordinateX(), cubeVertices[z][y+1][x].getCoordinateY(), cubeVertices[z][y+1][x].getCoordinateZ(), cubeVertices[z][y+1][x].getStatus());
					fprintf(GL_fl_DEBUG, "Vertice 6: (%d, %d, %d) ou (%d, %d, %d) : status %d\n", x+1, y+1, z, cubeVertices[z][y+1][x+1].getCoordinateX(), cubeVertices[z][y+1][x+1].getCoordinateY(), cubeVertices[z][y+1][x+1].getCoordinateZ(), cubeVertices[z][y+1][x+1].getStatus());
					fprintf(GL_fl_DEBUG, "Vertice 7: (%d, %d, %d) ou (%d, %d, %d) : status %d\n", x+1, y+1, z+1, cubeVertices[z+1][y+1][x+1].getCoordinateX(), cubeVertices[z+1][y+1][x+1].getCoordinateY(), cubeVertices[z+1][y+1][x+1].getCoordinateZ(), cubeVertices[z+1][y+1][x+1].getStatus());
					fprintf(GL_fl_DEBUG, "Vertice 8: (%d, %d, %d) ou (%d, %d, %d) : status %d\n", x, y+1, z+1, cubeVertices[z+1][y+1][x].getCoordinateX(), cubeVertices[z+1][y+1][x].getCoordinateY(), cubeVertices[z+1][y+1][x].getCoordinateZ(), cubeVertices[z+1][y+1][x].getStatus());
				} // </DEBUG>
			}
		}
	}
}


void vertexInterpolation(Vertex origin, Vertex master) {
	float x, y, z, point;


}