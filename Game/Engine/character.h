#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "texture.h"

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

typedef struct position {
    float x;
    float y;
} Position;

typedef struct hitbox {
    float height;
    float width;
    Position *origin;
} Hitbox;

typedef struct character {
    char name[100];
    int life;
    Position *position;
    Hitbox *hitbox;
    GLuint textureId1;
    GLuint textureId2;
} Character;

Character *initializeCharacter(char *name, float x, float y, float height, float width, char *textureName1, char *textureName2);

#endif