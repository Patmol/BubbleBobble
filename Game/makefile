CC=gcc
CFLAGS=-Wall -std=c99 -framework OpenGL -framework GLUT -lm -g -Wno-deprecated
OBJ=texture.o character.o weapon.o hitbox.o tga.o home.o end_game.o game.o glut.o main.o

bubble: $(OBJ)
	$(CC) -o BubbleBobble $(OBJ) $(CFLAGS)

tga.o: Engine/tga.h Engine/tga.c
	$(CC) -c Engine/tga.c -o tga.o $(CFLAGS)

weapon.o: Engine/weapon.h Engine/weapon.c
	$(CC) -c Engine/weapon.c -o weapon.o $(CFLAGS)

hitbox.o: Engine/hitbox.h Engine/hitbox.c
	$(CC) -c Engine/hitbox.c -o hitbox.o $(CFLAGS)

character.o: Engine/character.h Engine/character.c
	$(CC) -c Engine/character.c -o character.o $(CFLAGS)

texture.o: Engine/texture.h Engine/texture.c
	$(CC) -c Engine/texture.c -o texture.o $(CFLAGS)

home.o: Core/home.h Core/home.c
	$(CC) -c Core/home.c -o home.o $(CFLAGS)

end_game.o: Core/end_game.h Core/end_game.c
	$(CC) -c Core/end_game.c -o end_game.o $(CFLAGS)

game.o: Core/game.h Core/game.c
	$(CC) -c Core/game.c -o game.o $(CFLAGS)

glut.o: Core/glut.h Core/glut.c
	$(CC) -c Core/glut.c -o glut.o $(CFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

clean:
	rm -f *.o
	rm -f BubbleBobble