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
	./imageSimilarity ./entradas/picture_1_saida.bmp ./entradas/picture_1_entrada.bmp_saida.bmp
	./imageSimilarity ./entradas/picture_2_saida.bmp ./entradas/picture_2_entrada.bmp_saida.bmp
	./imageSimilarity ./entradas/picture_3_saida.bmp ./entradas/picture_3_entrada.bmp_saida.bmp
	./imageSimilarity ./entradas/picture_4_saida.bmp ./entradas/picture_4_entrada.bmp_saida.bmp
	./imageSimilarity ./entradas/picture_5_saida.bmp ./entradas/picture_5_entrada.bmp_saida.bmp