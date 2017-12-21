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
  float z = 0.0;
  int grayLevel[256] = { 0 };
	int totalGray = 0;
	float sk[256] = { 0 };

  for (int i = 0; i < imageSize; i += 3) {
    grayLevel[data[i]]++;
    totalGray++;
  }

  for (int i = 0; i < 256; ++i) {
    z += (float)((float)grayLevel[i]/(float)totalGray);
    sk[i] = z*256;
  }

  for (int i = 0; i < imageSize; i += 3) {
    data_histogram[i] = sk[data[i]];
    data_histogram[i+1] = sk[data[i]];
    data_histogram[i+2] = sk[data[i]];
  }
}

float gaussianFunction(int distance, int factor) {
	float eulerNumber = exp(-(pow(distance, 2)/(2*pow(factor, 2))));
	float firstPart = 1/(2*(PI*(pow(factor, 2))));
	float result = firstPart*eulerNumber;
	
	// <LOGGER>
	if (LOGGER) {
		fprintf(fl_LOGGER, "[gaussianFunction] -> return %f\n", result);
	} 
	// </LOGGER>

	return result;
}

float normalizationFactor(int processPixelPosition) {
	float Wp = 0;
	int processWindowPosition = 0;
	// <LOGGER>
	if (LOGGER) {
		fprintf(fl_LOGGER, "\n[normalizationFactor] - Iniciando\n");
	}
	// </LOGGER>
	for(int linePosition = -12; linePosition <= 12; linePosition += 3) {
		for(int columnPosition = -12; columnPosition <= 12; columnPosition += 3) {
			// <LOGGER>
			if (LOGGER) {
				fprintf(fl_LOGGER, "\t[normalizationFactor] - X na matriz: %d || Y na matriz: %d\n", linePosition, columnPosition);
			}
			// </LOGGER>

			processWindowPosition = processPixelPosition + (linePosition*width) + columnPosition;

			if (processWindowPosition < 0 || processWindowPosition > imageSize) {
				// <LOGGER>
				if (LOGGER) {
					fprintf(fl_LOGGER, "\t[normalizationFactor] - Valor fora da imagem\n");
				}
				// </LOGGER>
				Wp += 0;
			} else {
				Wp += gaussianFunction(abs(processPixelPosition - processWindowPosition), phiS) * gaussianFunction((data_histogram[processPixelPosition] - data_histogram[processWindowPosition]), phiR);
			}
		}
	}
	// <LOGGER>
	if (LOGGER) {
		fprintf(fl_LOGGER, "[normalizationFactor] - Finalizando -> return %f\n", Wp);
	}
	// </LOGGER>
	return Wp;
}

float bfNormalizationFactorWithExtra(int processPixelPosition) {
	float result = 0;
	int processWindowPosition = 0;
	// <LOGGER>
	if (LOGGER) {
		fprintf(fl_LOGGER, "\n[bfNormalizationFactorWithExtra] - Iniciando\n");
	}
	// </LOGGER>
	for(int linePosition = -12; linePosition <= 12; linePosition += 3) {
		for(int columnPosition = -12; columnPosition <= 12; columnPosition += 3) {
			// <LOGGER>
			if (LOGGER) {
				fprintf(fl_LOGGER, "\t[bfNormalizationFactorWithExtra] - X na matriz: %d || Y na matriz: %d\n", linePosition, columnPosition);
			}
			// </LOGGER>
			processWindowPosition = processPixelPosition + ((linePosition*width) + columnPosition);

			if (processWindowPosition < 0 || processWindowPosition > imageSize) {
				// <LOGGER>
				if (LOGGER) {
					fprintf(fl_LOGGER, "[bfNormalizationFactorWithExtra] - Valor fora da matrix\n");
				}
				// </LOGGER>
				result += 0;
			} else {
				result += (gaussianFunction(abs(processPixelPosition - processWindowPosition), phiS) * gaussianFunction((data_histogram[processPixelPosition] - data_histogram[processWindowPosition]), phiR)) * data_histogram[processWindowPosition];
			}
		}
	}
	// <LOGGER>
	if (LOGGER) {
		fprintf(fl_LOGGER, "[bfNormalizationFactorWithExtra] - Finalizando -> return %f\n", result);
	}
	// </LOGGER>
	return result;
}

void bilateralFilter() {
	for(int p = 0; p < imageSize ; p += 3) {
		int result = static_cast<int>(((1/normalizationFactor(p))*bfNormalizationFactorWithExtra(p)));
		unsigned char BF = (unsigned char)result;
		newImageData[p] = BF;
		newImageData[p+1] = BF;
		newImageData[p+2] = BF;
		// <LOGGER>
		if (LOGGER) {
			fprintf(fl_LOGGER, "\n\t[bilateralFilter] - Pixel é: %d de %d\n", p, (width * height));
			fprintf(fl_LOGGER, "\t[bilateralFilter] - BF value: %c\n", BF);
		}
		// </LOGGER>
	}
}

void saveImageBMP(const char *fileName) {
	FILE *bmpFile = fopen(fileName,"w+");

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
	// <LOGGER>
	if (LOGGER) {
		fprintf(fl_LOGGER, "[getImageName] - Iniciando\n");
	}
	// </LOGGER>

	int len = strlen(argv[1]);
  char *fileName = new char[len+6];
	strncpy(fileName, argv[1], len-4);	
	strcat(fileName, "-saida.bmp");
	// <LOGGER>
	if (LOGGER){
		fprintf(fl_LOGGER, "\t[getImageName] - Nome da Imagem é: %s\n", fileName);
		fprintf(fl_LOGGER, "\t[getImageName] - Finalizando\n");
	}
	// </LOGGER>
	return fileName;
}

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Uma imagem é necessaria\n");
		return 1;
	}
	// <LOGGER>
	if (LOGGER) {
		fl_LOGGER = fopen("imageRestoration.log", "w+" );
		fprintf(fl_LOGGER, "[main] - Iniciando Restauração de Imagem\n");
	} 
	// </LOGGER>

	loadImageBMP(argv[1]);
	histogram();
	bilateralFilter();

	saveImageBMP(getImageName(argv));
		
	// <LOGGER>
	if (LOGGER) {
		fprintf(fl_LOGGER, "[main] - Finalizando processamento e exibindo tela\n");
		fclose( fl_LOGGER );
	} 
	// </LOGGER>

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