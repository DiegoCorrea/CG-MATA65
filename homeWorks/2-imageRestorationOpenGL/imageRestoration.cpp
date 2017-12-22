# include <GL/glut.h>
# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# define PI 3.14
using namespace std;

const bool LOGGER = false;
FILE *fl_LOGGER;


// BMP
unsigned char header[54];   		// Each BMP file begins by a 54-bytes header
unsigned int dataPos;       		// Position in the file where the actual data begins
unsigned int width, height; 		// Image width and height
unsigned int imageSize;     		// width*height*channels
unsigned char* data;        		// Actual RGB data
unsigned char* newImageData;		// Actual RGB data
unsigned char* data_histogram;	// Actual RGB data

const int phiS = 3;
const int phiR = 8;

void histogram() {
  double z = 0.0;
  int grayLevel[256] = { 0 };
	int totalGray = 0;
	double sk[256] = { 0 };

  for (int i = 0; i < imageSize; i += 3) {
    grayLevel[data[i]]++;
    totalGray++;
  }

  for (int i = 0; i < 256; ++i) {
    z += (double)((double)grayLevel[i]/(double)totalGray);
    sk[i] = z*256;
  }

  for (int i = 0; i < imageSize; i += 3) {
    data_histogram[i] = sk[data[i]];
    data_histogram[i+1] = sk[data[i]];
    data_histogram[i+2] = sk[data[i]];
  }
}

double euclideanDistance(int baseX, int compareX, int baseY, int compareY) {
	return sqrt(pow(compareX - baseX, 2.0) + pow(compareY - baseY, 2.0));
}

double gaussianFunction(double distance, int factor) {
	double eulerNumber = exp(-(pow(distance, 2)/(2*pow(factor, 2))));
	double firstPart = 1/(2*(PI*(pow(factor, 2))));

	return firstPart*eulerNumber;
}

double normalizationFactor(int processPixelPosition) {
	double Wp = 0.0;
	int processWindowPosition = 0;
	int comparePixelWidth, comparePixelHeight, basePixelWidth, basePixelHeight;

	for(int linePosition = -12; linePosition <= 12; linePosition += 3) {
		for(int columnPosition = -12; columnPosition <= 12; columnPosition += 3) {
			processWindowPosition = processPixelPosition + (linePosition*width) + columnPosition;
			if (processWindowPosition < 0 || processWindowPosition > imageSize) {
				Wp += 0.0;
			} else {
				comparePixelWidth = processWindowPosition / (width*3);
				comparePixelHeight = processWindowPosition / (height*3);

				basePixelWidth = processPixelPosition / (width*3);
				basePixelHeight = processPixelPosition / (height*3);

				if((abs(basePixelWidth - comparePixelWidth) > 4) || (abs(basePixelHeight - comparePixelHeight) > 4)){
					Wp += 0.0;
				} else {
					Wp += gaussianFunction(euclideanDistance(basePixelWidth, comparePixelWidth, basePixelHeight, comparePixelHeight), phiS) * gaussianFunction((data_histogram[processPixelPosition] - data_histogram[processWindowPosition]), phiR);
				}
			}
		}
	}
	return Wp;
}

double bfNormalizationFactorWithExtra(int processPixelPosition) {
	double result = 0.0;
	int processWindowPosition = 0;
	int comparePixelWidth, comparePixelHeight, basePixelWidth, basePixelHeight;

	for(int linePosition = -12; linePosition <= 12; linePosition += 3) {
		for(int columnPosition = -12; columnPosition <= 12; columnPosition += 3) {
			processWindowPosition = processPixelPosition + ((linePosition*width) + columnPosition);
			if (processWindowPosition < 0 || processWindowPosition > imageSize) {
				result += 0.0;
			} else {
				comparePixelWidth = (processWindowPosition / (width*3));
				comparePixelHeight = (processWindowPosition / (height*3));

				basePixelWidth = (processPixelPosition / (width*3));
				basePixelHeight = (processPixelPosition / (height*3));

				if((abs(basePixelWidth - comparePixelWidth) > 4) || (abs(basePixelHeight - comparePixelHeight) > 4)){
					result += 0.0;
				} else {
					result += gaussianFunction(euclideanDistance(basePixelWidth, comparePixelWidth, basePixelHeight, comparePixelHeight), phiS) * gaussianFunction((data_histogram[processPixelPosition] - data_histogram[processWindowPosition]), phiR) * data_histogram[processWindowPosition];
				}
			}
		}
	}
	return result;
}

void bilateralFilter() {
	int widthPosition = 0, level = 0;
	for(int p = 0; p < imageSize ; p += 3) {
		int result = static_cast<int>(((1/normalizationFactor(p))*bfNormalizationFactorWithExtra(p)));
		unsigned char BF = (unsigned char)result;
		newImageData[p] = BF;
		newImageData[p+1] = BF;
		newImageData[p+2] = BF;
	}
}

void saveImageBMP(const char *fileName) {
	FILE *bmpFile = fopen(fileName,"wb");

	fwrite(header, 1, 54, bmpFile);
	fwrite(newImageData, 1, imageSize, bmpFile);

	fclose(bmpFile);
}


int loadImageBMP(const char *imagepath) {
	// Open the file
	FILE *file = fopen(imagepath,"rb");
	if (!file) {
		printf("O arquivo não pode ser aberto\n"); 
		return 0;
	}

	if ( fread(header, 1, 54, file)!=54 ) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return 0;
	}

	if ( header[0]!='B' || header[1]!='M' ) {
		printf("Not a correct BMP file\n");
		return 0;
	}

	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	imageSize  = *(int*)&(header[0x22]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)
		imageSize = width*height*3; // 3 channels : one byte for each Red, Green and Blue component
	if (dataPos == 0)
		dataPos = 54; // The BMP header is done that way


	// Create a buffer
	data = (unsigned char *)malloc(imageSize);
	data_histogram = (unsigned char *)malloc(imageSize);
	newImageData = (unsigned char *)malloc(imageSize);	

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);

	//Everything is in memory now, the file can be closed
	fclose(file);
}

void init(void) {
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glRasterPos2i (0, 0);
  glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

  glRasterPos2i (width, 0);
  glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, newImageData);
  glFlush();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho (0, w, 0, h, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
      exit(0);
  }
}

char *getImageName(char **argv) {
	int len = strlen(argv[1]);
  char *fileName = new char[len+15];
	strcpy(fileName, argv[1]);	
	strcat(fileName, "_saida.bmp\0");
	return fileName;
}

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Uma imagem é necessaria\n");
		return 1;
	}

	loadImageBMP(argv[1]);
	histogram();
	bilateralFilter();

	saveImageBMP(getImageName(argv));
		
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width*2, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}