# include <stdio.h>
# include <stdlib.h>

// BMP
unsigned char baseHeader[54], compareHeader[54];
unsigned int baseWidth, baseHeight, compareWidth, compareHeight;
unsigned int baseImageSize, compareImageSize;
unsigned char *base, *compare;


float imageSimilarity() {
	int matrixSum = 0;
	for(int pixel = 0; pixel < baseImageSize; pixel += 3) {
		matrixSum += abs(base[pixel] - compare[pixel]);
	}
	float result = (1-(matrixSum/(baseHeight*baseWidth*255)))*100;
	return result;
}

int loadImages(const char *basepath, const char *comparepath) {
	// Open the file
	FILE *fileBase = fopen(basepath,"rb");
	FILE *fileCompare = fopen(comparepath,"rb");
	if (!fileBase || !fileCompare) {
		printf("O arquivo não pode ser aberto\n"); 
		return 0;
	}

	if ( fread(baseHeader, 1, 54, fileBase) != 54 || fread(compareHeader, 1, 54, fileCompare) != 54 ) { // If not 54 bytes read : problem
		printf("Arquivo não BMP\n");
		return 0;
	}

	// Read ints from the byte array
	baseWidth      = *(int*)&(baseHeader[0x12]);
	baseHeight     = *(int*)&(baseHeader[0x16]);
	baseImageSize  = *(int*)&(baseHeader[0x22]);

	compareWidth      = *(int*)&(compareHeader[0x12]);
	compareHeight     = *(int*)&(compareHeader[0x16]);
	compareImageSize  = *(int*)&(compareHeader[0x22]);

	if( baseWidth != compareWidth || baseHeight != compareHeight) {
		printf("Tamanhos diferentes Width | %d -> %d || Height | %d -> %d \n", baseWidth, compareWidth, baseHeight, compareHeight);
		exit(0);
	}

	// Create a buffer
	base = (unsigned char *)malloc(baseImageSize);
	compare = (unsigned char *)malloc(compareImageSize);

	// Read the actual data from the file into the buffer
	fread(base, 1, baseImageSize, fileBase);
	fread(compare, 1, compareImageSize, fileCompare);

	//Everything is in memory now, the file can be closed
	fclose(fileBase);
	fclose(fileCompare);
}

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Uma imagem é necessaria\n");
		return 1;
	}

	loadImages(argv[1], argv[2]);

	printf("\nSimilaridade da imagem %s com %s \t\t-> %f\n\n", argv[1], argv[2], imageSimilarity());

	return 0;
}