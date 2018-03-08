#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "texture.h"

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

typedef enum movement {
    NONE,
    LEFT,
    RIGHT
} Movement;

typedef struct position {
    float x;
    float y;
} Position;

typedef struct hitbox {
    float height;
    float width;
    Position *origin;
} Hitbox;

typedef struct characterTexture {
    char name[50];
    GLuint textureId;
} CharacterTexture;

typedef struct character {
    char name[100];
    int life;
    Position *position;
    Hitbox *hitbox;
    Movement move;
    int indexTexture;
    CharacterTexture characterTexture[10];
} Character;

Character *initializeCharacter(char *name, float x, float y, float height, float width);
void addCharacterTexture(Character *character, char *textureName, char name[50]);
GLuint getCharacterTexture(Character *character, char name[50]);

#endif