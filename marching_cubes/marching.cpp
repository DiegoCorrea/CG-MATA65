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

class Vertex{
  private:
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

class Grid{
	int planSize;
	float isoValue;
	vector<vector<vector<Vertex> > > vertices;

	public:
		Grid(){ }

		int getPlanSize(){
    	return this->planSize;
    }

    int getIsoValue(){
    	return this->isoValue;
    }

    bool setIsoValue(int newIsoValue){
    	this->isoValue = newIsoValue;
    	return true;
    }

		void addVertex(int x, int y, int z, int status){
			int id = vertices.size();
      Vertex vertex(x, y, z, status, id);

      this->vertices[z][y][x] = vertex;
    }

    /*
    bool makePlan(int newPlanSize){
    	if(newPlanSize < 1){	
    		return false;
    	}

    	this->planSize = newPlanSize;
    	// Set up sizes. (planSize x planSize x planSize)
		  this->vertices.resize(newPlanSize);
		  for (int x = 0; x < newPlanSize; ++x){
		    this->vertices[x].resize(newPlanSize);
		    for (int y = 0; y < newPlanSize; ++y){
		      this->vertices[y][x].resize(newPlanSize);
		    }
		  }

		  return true;
    }
    */

    // <DEBUG>
    void allVertex() {
    	int size_vertices = this->vertices.size();

    	for(int x = 0; x < size_vertices; x++){
    		for(int y = 0; y < size_vertices; y++){
    			for(int z = 0; z < size_vertices; z++){
   					fprintf(GL_fl_DEBUG, "[GRID] ID: %d - (%d, %d, %d) - Status %d\n", this->vertices[z][y][x].getID(), this->vertices[z][y][x].getCoordinateX(), this->vertices[z][y][x].getCoordinateY(), this->vertices[z][y][x].getCoordinateZ(), this->vertices[z][y][x].getStatus());
    			}
    		}
    	}
    } // </DEBUG>
};

Grid Space;

void readFile(int argc, char *argv[]);

int main(int argc, char *argv[]) {	
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

  for(int i = 0; i < LUTLINES; i++) {
  	for(int j = 0; j < LUTCOLUMN; j++){
  	  fscanf(fl_input, "%d", &LUT[i][j]);
  	}
  }

  // <DEBUG>
	if (DEBUG == 1){
		for(int i = 0; i < LUTLINES; i++) {
			fprintf(GL_fl_DEBUG, "[readFile] Linha '%d': - ", i+1);
	    
	    for(int j = 0; j < LUTCOLUMN; j++){
				fprintf(GL_fl_DEBUG, "%d ", LUT[i][j]);
	    }
	  	fprintf(GL_fl_DEBUG, "\n");
	  }
	} // </DEBUG>

	int planSize;
	fscanf(fl_input, "%d", &planSize);
	int v[planSize][planSize][planSize];
	//Space.makePlan(planSize);

	for(int z = 0; z < planSize; z++){
		for(int y = 0; y < planSize; y++) {
			for (int x = 0; x < planSize; ++x) {
				fscanf(fl_input, "%d", &v[z][y][x]);
				//Space.addVertex(x,-y,-z,v[z][y][x]);
			}
		}
	}

	// <DEBUG>
	if (DEBUG == 1){
		fprintf(GL_fl_DEBUG, "[readFile] - O tamanho do Plano é: '%d'\n", planSize);
		for(int z = 0; z < planSize; z++){
			for(int y = 0; y < planSize; y++){
				for (int x = 0; x < planSize; ++x){
					fprintf(GL_fl_DEBUG, "%d ", v[z][y][x]);
				}
				fprintf(GL_fl_DEBUG, "\n");
			}
		}
	} // </DEBUG>


	//Space.allVertex();

	float isoValue;
	fscanf(fl_input, "%f", &isoValue);
	Space.setIsoValue(isoValue);

	fprintf(GL_fl_DEBUG, "[readFile] - O Iso Valor é: %f \n", isoValue);

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