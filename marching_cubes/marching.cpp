using namespace std;
# include <stdlib.h>
# include <vector>
# include <cmath>
# include <algorithm>
# include <iostream>
# include <iomanip>
# include <numeric>
# include <iterator>
# include <limits>
# include <string.h>
# include <stdio.h>
# include <math.h>

# define DEBUG 0
# define TRUE 1
# define FALSE 0
# define LUTLINES 256
# define LUTCOLUMN 16
# define OUTPUT "malha.obj"

FILE *GL_fl_DEBUG;
int LUT[LUTLINES][LUTCOLUMN+1] = { -1 };
int planSize;
float isoValue;

class Vertex{
  private:
  	int coordinateX, coordinateY, coordinateZ;
  	int value, id;

  public:
    Vertex(int x, int y, int z, int value){
      this->coordinateX = x;
      this->coordinateY = y;
      this->coordinateZ = z;
      this->value = value;
    }

    Vertex(int x, int y, int z, int value, int id){
      this->coordinateX = x;
      this->coordinateY = y;
      this->coordinateZ = z;
      this->value = value;
      this->id = id;
    }

    Vertex(){ };

    ~Vertex(){ };

    int getCoordinateX(){
      return this->coordinateX;
    }

    int getCoordinateY(){
      return this->coordinateY;
    }

    int getCoordinateZ(){
      return this->coordinateZ;
    }

    int getValue(){
    	return this->value;
    }

    int isMarked(){
    	if (this->value > 0) {
    		return TRUE;
    	}
    	return FALSE;
    }

    int getId(){
    	return this->id;
    }
};
vector<vector<vector<Vertex> > > spaceVertices;

class VertexOfTheObject{
  private:
  	float coordinateX, coordinateY, coordinateZ;
  	float value;
  	int id;

  public:
    VertexOfTheObject(float x, float y, float z, float value){
      this->coordinateX = x;
      this->coordinateY = y;
      this->coordinateZ = z;
      this->value = value;
    }

    VertexOfTheObject(float x, float y, float z, float value, int id){
      this->coordinateX = x;
      this->coordinateY = y;
      this->coordinateZ = z;
      this->value = value;
      this->id = id;
    }

    VertexOfTheObject(){ };

    ~VertexOfTheObject(){ };

    float getCoordinateX(){
      return this->coordinateX;
    }

    float getCoordinateY(){
      return this->coordinateY;
    }

    float getCoordinateZ(){
      return this->coordinateZ;
    }

    float getValue(){
    	return this->value;
    }

    int getId(){
    	return this->id;
    }	

    void setId(int id){
    	this->id = id;
    }
};
std::vector<VertexOfTheObject> newVertices;

class Triangule {
	private:
		VertexOfTheObject coordinates[3];

	public:
		Triangule(VertexOfTheObject first, VertexOfTheObject middle, VertexOfTheObject end){
			this->coordinates[0] = first;
			this->coordinates[1] = middle;
			this->coordinates[2] = end;

		}

		~Triangule(){ }

		VertexOfTheObject* getCoordinates(){
			return this->coordinates;
		}

};
std::vector<Triangule> trianguleOfTheObjects;

class Cube {
	private:
		Vertex *vertices[8];
		int binaryConfig[8];
		int decimalConfig;
		int id;
	public:
		Cube(int x, int y, int z, int id){
			this->vertices[0] = &spaceVertices[z][y][x];
			this->vertices[1] = &spaceVertices[z][y][x+1];
			this->vertices[2] = &spaceVertices[z+1][y][x+1];
			this->vertices[3] = &spaceVertices[z+1][y][x];
			this->vertices[4] = &spaceVertices[z][y+1][x];
			this->vertices[5] = &spaceVertices[z][y+1][x+1];
			this->vertices[6] = &spaceVertices[z+1][y+1][x+1];
			this->vertices[7] = &spaceVertices[z+1][y+1][x];

			this->id = id;
		}

		~Cube(){ };

		Vertex* getVertex(int position){
			return this->vertices[position];
		}

		void setBinaryConfig(int vec[8]){
			for (int i = 0; i < 8; ++i){
				this->binaryConfig[i] = vec[i];
			}
		}

		void setDecimalConfig(int dec){
			this->decimalConfig = dec;
		}

		int getDecimalConfig(){
			return this->decimalConfig;
		}

		int getId(){
			return this->id;
		}

		void printVerteces(){
			fprintf(GL_fl_DEBUG, "\n[printVerteces] - Cubo %d - Possui a configuração: %d\n", this->id, this->decimalConfig);
			fprintf(GL_fl_DEBUG, "[printVerteces] - Vertices usados: ");
			for(int j = 0; j < LUTCOLUMN; j++){
				fprintf(GL_fl_DEBUG, "%d ", LUT[decimalConfig][j]);
  		}
			fprintf(GL_fl_DEBUG, "\n");
			fprintf(GL_fl_DEBUG, "[printVerteces] - Vertice 0: Global ID %d \t(%d, %d, %d) : Valor %d\n", this->vertices[0]->getId() ,this->vertices[0]->getCoordinateX(), this->vertices[0]->getCoordinateY(), this->vertices[0]->getCoordinateZ(), this->vertices[0]->getValue());
			fprintf(GL_fl_DEBUG, "[printVerteces] - Vertice 1: Global ID %d \t(%d, %d, %d) : Valor %d\n", this->vertices[1]->getId() ,this->vertices[1]->getCoordinateX(), this->vertices[1]->getCoordinateY(), this->vertices[1]->getCoordinateZ(), this->vertices[1]->getValue());
			fprintf(GL_fl_DEBUG, "[printVerteces] - Vertice 2: Global ID %d \t(%d, %d, %d) : Valor %d\n", this->vertices[2]->getId() ,this->vertices[2]->getCoordinateX(), this->vertices[2]->getCoordinateY(), this->vertices[2]->getCoordinateZ(), this->vertices[2]->getValue());
			fprintf(GL_fl_DEBUG, "[printVerteces] - Vertice 3: Global ID %d \t(%d, %d, %d) : Valor %d\n", this->vertices[3]->getId() ,this->vertices[3]->getCoordinateX(), this->vertices[3]->getCoordinateY(), this->vertices[3]->getCoordinateZ(), this->vertices[3]->getValue());
			fprintf(GL_fl_DEBUG, "[printVerteces] - Vertice 4: Global ID %d \t(%d, %d, %d) : Valor %d\n", this->vertices[4]->getId() ,this->vertices[4]->getCoordinateX(), this->vertices[4]->getCoordinateY(), this->vertices[4]->getCoordinateZ(), this->vertices[4]->getValue());
			fprintf(GL_fl_DEBUG, "[printVerteces] - Vertice 5: Global ID %d \t(%d, %d, %d) : Valor %d\n", this->vertices[5]->getId() ,this->vertices[5]->getCoordinateX(), this->vertices[5]->getCoordinateY(), this->vertices[5]->getCoordinateZ(), this->vertices[5]->getValue());
			fprintf(GL_fl_DEBUG, "[printVerteces] - Vertice 6: Global ID %d \t(%d, %d, %d) : Valor %d\n", this->vertices[6]->getId() ,this->vertices[6]->getCoordinateX(), this->vertices[6]->getCoordinateY(), this->vertices[6]->getCoordinateZ(), this->vertices[6]->getValue());
			fprintf(GL_fl_DEBUG, "[printVerteces] - Vertice 7: Global ID %d \t(%d, %d, %d) : Valor %d\n", this->vertices[7]->getId() ,this->vertices[7]->getCoordinateX(), this->vertices[7]->getCoordinateY(), this->vertices[7]->getCoordinateZ(), this->vertices[7]->getValue());
		}
};
vector<Cube> spaceCubes;

void allVertex();
int convertBinaryToDecimal(long long n);
void readFile(int argc, char *argv[]);
void makeCubes();
VertexOfTheObject vertexInterpolation(Vertex *origin, Vertex *master);
VertexOfTheObject insertNotDuplicate(VertexOfTheObject vertex);
void cubeInterpolation(Cube *cube);
VertexOfTheObject edgeVertices(Cube *cube, int edge);
void cubeInter(Cube *cube);
void printAllNewVertices();
void printAllTriangules();
void printOBJ();

int main(int argc, char *argv[]){	
	if (argc < 2){
		printf("Para executar é necessario um arquivo de entrada\n");
		printf("O Marching Cubes será fechado!\n");
		return 1;
	}
	// <DEBUG>
	if (DEBUG == 1){
		GL_fl_DEBUG = fopen("marchingDEBUG.log", "w+" );
		fprintf(GL_fl_DEBUG, "[main] - Iniciando Programa\n");
	} // </DEBUG>


	readFile(argc, argv);
	makeCubes();

	printOBJ();

	// <DEBUG>
	if (DEBUG == 1){
		fclose( GL_fl_DEBUG );
	} // </DEBUG>

	return 0;
}

// <DEBUG>
void allVertex() {
	for(int x = 0; x < planSize; x++){
		for(int y = 0; y < planSize; y++){
			for(int z = 0; z < planSize; z++){
				fprintf(GL_fl_DEBUG, "[GRID] - (%d, %d, %d) - Status %d\n", spaceVertices[z][y][x].getCoordinateX(), spaceVertices[z][y][x].getCoordinateY(), spaceVertices[z][y][x].getCoordinateZ(), spaceVertices[z][y][x].getValue());
			}
		}
	}
} // </DEBUG>

void readFile(int argc, char *argv[]){
	FILE *fl_input;
	// <DEBUG>
	if (DEBUG == 1){
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
	int vertexCounter = 0;

	for(int z = 0; z < planSize; z++){
		vector < vector < Vertex > > d2;
		spaceVertices.push_back( d2 );
		for(int y = 0; y < planSize; y++) {
			vector <Vertex> d3;
      spaceVertices[z].push_back( d3 );
			for (int x = 0; x < planSize; ++x, vertexCounter++) {
				fscanf(fl_input, "%d", &v[z][y][x]);

				Vertex vertice(x,y,z,v[z][y][x],vertexCounter);
        spaceVertices[z][y].push_back(vertice);
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
		fprintf(GL_fl_DEBUG, "[readFile] - Finalizando Função\n");
		fprintf(GL_fl_DEBUG, "\n\n");
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

void makeCubes(){
	int totalCubes = (planSize-1)*(planSize-1)*(planSize-1);
	int binaryConfig[8], decimalConfig = 0;

	// <DEBUG>
	if (DEBUG == 1){
		fprintf(GL_fl_DEBUG, "[makeCubes] --- Iniciando Produção dos Cubos\n");
	}// </DEBUG>

	for(int z = 0, cubesCounter = 0; z < planSize-1; z++){
		for(int y = 0; y < planSize-1; y++ ) {
			for(int x = 0; x < planSize-1; x++, cubesCounter++){
				int id = 0;

				binaryConfig[0] = spaceVertices[z+1][y+1][x].isMarked();
				binaryConfig[1] = spaceVertices[z+1][y+1][x+1].isMarked();
				binaryConfig[2] = spaceVertices[z][y+1][x+1].isMarked();
				binaryConfig[3] = spaceVertices[z][y+1][x].isMarked();
				binaryConfig[4] = spaceVertices[z+1][y][x].isMarked();
				binaryConfig[5] = spaceVertices[z+1][y][x+1].isMarked();
				binaryConfig[6] = spaceVertices[z][y][x+1].isMarked();
				binaryConfig[7] = spaceVertices[z][y][x].isMarked();

				decimalConfig = convertBinaryToDecimal(makeBinary(binaryConfig));
				Cube cube(x, y, z, cubesCounter);
				cube.setDecimalConfig(decimalConfig);
				cube.setBinaryConfig(binaryConfig);
				spaceCubes.push_back(cube);
				cubeInter(&cube);

				// <DEBUG>
				if (DEBUG == 1){
	    		cube.printVerteces();

					fprintf(GL_fl_DEBUG, "\n");
					fprintf(GL_fl_DEBUG, "[makeCubes] - Reconhecendo Arestas\n");
					fprintf(GL_fl_DEBUG, "[makeCubes] - De (%d, %d, %d) para (%d, %d, %d) ID: %d\n", x,y,z, x+1,y,z, id);
					id++;
					fprintf(GL_fl_DEBUG, "[makeCubes] - De (%d, %d, %d) para (%d, %d, %d) ID: %d\n", x+1,y,z, x+1,y,z+1, id);
					id++;
					fprintf(GL_fl_DEBUG, "[makeCubes] - De (%d, %d, %d) para (%d, %d, %d) ID: %d\n", x+1,y,z+1, x,y,z+1, id);
					id++;
					fprintf(GL_fl_DEBUG, "[makeCubes] - De (%d, %d, %d) para (%d, %d, %d) ID: %d\n", x,y,z+1, x,y,z, id);
					id++;
					fprintf(GL_fl_DEBUG, "[makeCubes] - De (%d, %d, %d) para (%d, %d, %d) ID: %d\n", x,y+1,z, x+1,y+1,z, id);
					id++;
					fprintf(GL_fl_DEBUG, "[makeCubes] - De (%d, %d, %d) para (%d, %d, %d) ID: %d\n", x+1,y+1,z, x+1,y+1,z+1, id);
					id++;
					fprintf(GL_fl_DEBUG, "[makeCubes] - De (%d, %d, %d) para (%d, %d, %d) ID: %d\n", x+1,y+1,z+1, x,y+1,z+1, id);
					id++;
					fprintf(GL_fl_DEBUG, "[makeCubes] - De (%d, %d, %d) para (%d, %d, %d) ID: %d\n", x,y+1,z+1, x,y+1,z, id);
					id++;
					fprintf(GL_fl_DEBUG, "[makeCubes] - De (%d, %d, %d) para (%d, %d, %d) ID: %d\n", x,y,z, x,y+1,z, id);
					id++;
					fprintf(GL_fl_DEBUG, "[makeCubes] - De (%d, %d, %d) para (%d, %d, %d) ID: %d\n", x+1,y,z, x+1,y+1,z, id);
					id++;
					fprintf(GL_fl_DEBUG, "[makeCubes] - De (%d, %d, %d) para (%d, %d, %d) ID: %d\n", x+1,y,z+1, x+1,y+1,z+1, id);
					id++;
					fprintf(GL_fl_DEBUG, "[makeCubes] - De (%d, %d, %d) para (%d, %d, %d) ID: %d\n", x,y,z+1, x,y+1,z+1, id);
					id++;

					fprintf(GL_fl_DEBUG, "-------------------------------------------------------------------------------\n");
				} // </DEBUG>
			}
		}
	}
}

VertexOfTheObject vertexInterpolation(Vertex *origin, Vertex *master) {
	float x = 0, y = 0, z = 0, point;
	float dm, dt, p1, p2;

	dm = std::abs(isoValue - master->getValue());
	dt = std::abs(master->getValue() - origin->getValue());
	if (dm == 0 || dt ==0 ){
		p1 = 0;	
	}
	else {
		p1 = (dm / dt);
	}
	x = origin->getCoordinateX() * p1;
	y = origin->getCoordinateY() * p1;
	z = origin->getCoordinateZ() * p1;


	dm = std::abs(isoValue - origin->getValue());
	dt = std::abs(master->getValue() - origin->getValue());
	if (dm == 0 || dt ==0){
		p2 = 0;	
	}
	else {
		p2 = (dm / dt);
	}
	x += (master->getCoordinateX() * p2);
	y += (master->getCoordinateY() * p2);
	z += (master->getCoordinateZ() * p2);
	// <DEBUG>
	if (DEBUG == 1){
		fprintf(GL_fl_DEBUG, "\n[vertexInterpolation] - Novo vertice: (%f, %f, %f)\n", x, y, z);
	} // </DEBUG>

	VertexOfTheObject vertice(x,y,z,isoValue);
	return vertice;
}

VertexOfTheObject insertNotDuplicate(VertexOfTheObject vertex){
	int length = newVertices.size();

	for (int i = 0; i < length; ++i){
		if ((vertex.getCoordinateX() == newVertices[i].getCoordinateX()) && (vertex.getCoordinateY() == newVertices[i].getCoordinateY()) && (vertex.getCoordinateZ() == newVertices[i].getCoordinateZ())) {
			return newVertices[i];
		}
	}
	vertex.setId(newVertices.size()+1);
	newVertices.push_back(vertex);

	return vertex;
}

VertexOfTheObject edgeVertices(Cube *cube, int edge) {
	switch(edge){
		case 0:
			return vertexInterpolation(cube->getVertex(0), cube->getVertex(1));
		break;
		case 1:
			return vertexInterpolation(cube->getVertex(1), cube->getVertex(2));
		break;
		case 2:
			return vertexInterpolation(cube->getVertex(2), cube->getVertex(3));
		break;
		case 3:
			return vertexInterpolation(cube->getVertex(3), cube->getVertex(0));
		break;
		case 4:
			return vertexInterpolation(cube->getVertex(4), cube->getVertex(5));
		break;
		case 5:
			return vertexInterpolation(cube->getVertex(5), cube->getVertex(6));
		break;
		case 6:
			return vertexInterpolation(cube->getVertex(6), cube->getVertex(7));
		break;
		case 7:
			return vertexInterpolation(cube->getVertex(7), cube->getVertex(4));
		break;
		case 8:
			return vertexInterpolation(cube->getVertex(4), cube->getVertex(0));
		break;
		case 9:
			return vertexInterpolation(cube->getVertex(5), cube->getVertex(1));
		break;
		case 10:
			return vertexInterpolation(cube->getVertex(6), cube->getVertex(2));
		break;
		case 11:
			return vertexInterpolation(cube->getVertex(7), cube->getVertex(3));
		break;
		default:
			printf("FUDEUUUUUUUUUUUUUUUUUUUUUUUUUUU... ARESTA ÑÃO EXISTE\n");
	}
}

void cubeInter(Cube *cube){
	int edge = LUT[cube->getDecimalConfig()][0];
	for(int j = 0; j < 16 && edge != -1; j += 3, edge = LUT[cube->getDecimalConfig()][j]){
		Triangule tri(
			insertNotDuplicate((edgeVertices(cube, LUT[cube->getDecimalConfig()][j]))),
			insertNotDuplicate((edgeVertices(cube, LUT[cube->getDecimalConfig()][j+1]))),
			insertNotDuplicate((edgeVertices(cube, LUT[cube->getDecimalConfig()][j+2])))
		);
		trianguleOfTheObjects.push_back(tri);
  }
}

void cubeInterpolation(Cube *cube){
	VertexOfTheObject vertex;
	if(cube->getVertex(0)->isMarked() == TRUE ){
		Triangule tri(
			insertNotDuplicate(vertexInterpolation(cube->getVertex(0), cube->getVertex(1))),
			insertNotDuplicate(vertexInterpolation(cube->getVertex(0), cube->getVertex(4))),
			insertNotDuplicate(vertexInterpolation(cube->getVertex(0), cube->getVertex(3)))
			);
		trianguleOfTheObjects.push_back(tri);
	}
	if(cube->getVertex(1)->isMarked() == TRUE ){
		Triangule tri(insertNotDuplicate(vertexInterpolation(cube->getVertex(1), cube->getVertex(2)))
		,insertNotDuplicate(vertexInterpolation(cube->getVertex(1), cube->getVertex(5)))
		,insertNotDuplicate(vertexInterpolation(cube->getVertex(1), cube->getVertex(0)))
		);
		trianguleOfTheObjects.push_back(tri);
	}
	if(cube->getVertex(2)->isMarked() == TRUE ){
		Triangule tri(
		insertNotDuplicate(vertexInterpolation(cube->getVertex(2), cube->getVertex(3)))
		, insertNotDuplicate(vertexInterpolation(cube->getVertex(2), cube->getVertex(6)))
		, insertNotDuplicate(vertexInterpolation(cube->getVertex(2), cube->getVertex(1)))
		);
		trianguleOfTheObjects.push_back(tri);
	}
	if(cube->getVertex(3)->isMarked() == TRUE ){
		Triangule tri(
		insertNotDuplicate(vertexInterpolation(cube->getVertex(3), cube->getVertex(0)))
		, insertNotDuplicate(vertexInterpolation(cube->getVertex(3), cube->getVertex(7)))
		, insertNotDuplicate(vertexInterpolation(cube->getVertex(3), cube->getVertex(2)))
		);
		trianguleOfTheObjects.push_back(tri);
	}
	if(cube->getVertex(4)->isMarked() == TRUE ){
		Triangule tri(
		insertNotDuplicate(vertexInterpolation(cube->getVertex(4), cube->getVertex(5)))
		, insertNotDuplicate(vertexInterpolation(cube->getVertex(4), cube->getVertex(0)))
		, insertNotDuplicate(vertexInterpolation(cube->getVertex(4), cube->getVertex(7)))
		);
		trianguleOfTheObjects.push_back(tri);
	}
	if(cube->getVertex(5)->isMarked() == TRUE ){
		Triangule tri(
		insertNotDuplicate(vertexInterpolation(cube->getVertex(5), cube->getVertex(6)))
		, insertNotDuplicate(vertexInterpolation(cube->getVertex(5), cube->getVertex(1)))
		, insertNotDuplicate(vertexInterpolation(cube->getVertex(5), cube->getVertex(4)))
		);
		trianguleOfTheObjects.push_back(tri);
	}
	if(cube->getVertex(6)->isMarked() == TRUE ){
		Triangule tri(
		insertNotDuplicate(vertexInterpolation(cube->getVertex(6), cube->getVertex(7)))
		, insertNotDuplicate(vertexInterpolation(cube->getVertex(6), cube->getVertex(2)))
		, insertNotDuplicate(vertexInterpolation(cube->getVertex(6), cube->getVertex(5)))
		);
		trianguleOfTheObjects.push_back(tri);
	}
	if(cube->getVertex(7)->isMarked() == TRUE ){
		Triangule tri(
		insertNotDuplicate(vertexInterpolation(cube->getVertex(7), cube->getVertex(4)))
		, insertNotDuplicate(vertexInterpolation(cube->getVertex(7), cube->getVertex(3)))
		, insertNotDuplicate(vertexInterpolation(cube->getVertex(7), cube->getVertex(6)))
		);
		trianguleOfTheObjects.push_back(tri);
	}
}

void printAllNewVertices(){
	int length = newVertices.size();

	for (int i = 0; i < length; ++i){
		fprintf(GL_fl_DEBUG, "v %.2f %.2f %.2f\n", newVertices[i].getCoordinateX(), newVertices[i].getCoordinateY(), newVertices[i].getCoordinateZ());
	}
}

void printAllTriangules(){
	int count = trianguleOfTheObjects.size();
	VertexOfTheObject *tmp;
	for (int i = 0; i < count; ++i){
		tmp = trianguleOfTheObjects[i].getCoordinates();
		fprintf(GL_fl_DEBUG, "f %d %d %d\n", tmp[0].getId(), tmp[1].getId(), tmp[2].getId());	
	}
}

void printOBJ(){
	FILE *fl_MALHA;
	int count = trianguleOfTheObjects.size();
	VertexOfTheObject *tmp;

	fl_MALHA = fopen(OUTPUT, "w+" );

	for (int i = 0; i < count; ++i){
		fprintf(fl_MALHA, "v %.2f %.2f %.2f\n", newVertices[i].getCoordinateX(), newVertices[i].getCoordinateY(), newVertices[i].getCoordinateZ());
	}

	for (int i = 0; i < count; ++i){
		tmp = trianguleOfTheObjects[i].getCoordinates();
		fprintf(fl_MALHA, "f %d %d %d\n", tmp[0].getId(), tmp[1].getId(), tmp[2].getId());	
	}

	fclose( fl_MALHA );
}