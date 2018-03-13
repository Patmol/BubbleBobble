#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdbool.h>

#include "texture.h"

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#define LEVEL_WIDTH 32
#define LEVEL_HEIGHT 25
#define PLAY_WIDTH_SIZE 1260
#define PLAY_HEIGHT_SIZE 880

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
    Movement prevMove;
    int indexTexture;
    float jumpHeight;
    bool isJumping;
    CharacterTexture characterTexture[10];
} Character;

Character *initializeCharacter(char *name, float x, float y, float height, float width);
/* Functions for the textures */
void addCharacterTexture(Character *character, char *textureName, char name[50]);
GLuint getCharacterTexture(Character *character, char name[50]);
/* Functions use to move the character */
void move(Character *character, int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT]);
void jump(Character *character, int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT]);

#endif