CC=gcc
CFLAGS = -std=c99 -Wall
OBJ=texture.o tga.o glut.o main.o

bubble: $(OBJ)
	$(CC) -o BubbleBobble $(OBJ) $(CFLAGS)

tga.o: Engine/tga.h Engine/tga.c
	$(CC) -c Engine/tga.c -o tga.o $(CFLAGS)

texture.o: Engine/texture.h Engine/texture.c
	$(CC) -c Engine/texture.c -o texture.o $(CFLAGS)

glut.o: Core/glut.h Core/glut.c
	$(CC) -c Core/glut.c -o glut.o $(CFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

clean:
	rm -f *.o
	rm -f BubbleBobble
	rm -f *~