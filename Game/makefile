CC=gcc
CFLAGS=-Wall -std=c99 -framework OpenGL -framework GLUT -lm -g -Wno-deprecated
OBJ=texture.o tga.o home.o game.o glut.o main.o

bubble: $(OBJ)
	$(CC) -o BubbleBobble $(OBJ) $(CFLAGS)

tga.o: Engine/tga.h Engine/tga.c
	$(CC) -c Engine/tga.c -o tga.o $(CFLAGS)

texture.o: Engine/texture.h Engine/texture.c
	$(CC) -c Engine/texture.c -o texture.o $(CFLAGS)

home.o: Core/home.h Core/home.c
	$(CC) -c Core/home.c -o home.o $(CFLAGS)

game.o: Core/game.h Core/game.c
	$(CC) -c Core/game.c -o game.o $(CFLAGS)

glut.o: Core/glut.h Core/glut.c
	$(CC) -c Core/glut.c -o glut.o $(CFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

clean:
	rm -f *.o
	rm -f BubbleBobble
	rm -f *~