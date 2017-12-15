# include <GL/glut.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

using namespace std;

// BMP
unsigned char header[54];
unsigned int dataPos;
unsigned int width, height;
unsigned int imageSize;
unsigned char* base;
unsigned char* compare;


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

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Uma imagem é necessaria\n");
		return 1;
	}
}