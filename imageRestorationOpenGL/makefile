all: 
	g++ -o imageRestoration imageRestoration.cpp -lglut -lGLU -lGL -lm
	gcc -o imageSimilarity imageSimilarity.c

run:
	./imageRestoration ./entradas/cidade.bmp
	./imageRestoration ./entradas/porta.bmp
	./imageRestoration ./entradas/impressao_digital.bmp
	./imageRestoration ./entradas/picture_1_entrada.bmp
	./imageRestoration ./entradas/picture_2_entrada.bmp
	./imageRestoration ./entradas/picture_3_entrada.bmp
	./imageRestoration ./entradas/picture_4_entrada.bmp
	./imageRestoration ./entradas/picture_5_entrada.bmp

similarity:
	./imageSimilarity ./entradas/picture_1_entrada.bmp ./entradas/picture_1_entrada-saida.bmp
	./imageSimilarity ./entradas/picture_2_entrada.bmp ./entradas/picture_2_entrada-saida.bmp
	./imageSimilarity ./entradas/picture_3_entrada.bmp ./entradas/picture_3_entrada-saida.bmp
	./imageSimilarity ./entradas/picture_4_entrada.bmp ./entradas/picture_4_entrada-saida.bmp
	./imageSimilarity ./entradas/picture_5_entrada.bmp ./entradas/picture_5_entrada-saida.bmp