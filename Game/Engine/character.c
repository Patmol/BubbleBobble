#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <string.h>

#include "texture.h"
#include "character.h"

#define X_MOVEMENT 10
#define Y_MOVEMENT 15
#define JUMP_HEIGHT 290

int startJump = 0;

Character *initializeCharacter(char *name, float x, float y, float height, float width) {
    Character *character = malloc(sizeof(Character));
    strcpy(character->name, name);
    character->life = 100;
    character->prevMove = RIGHT;
    character->move = NONE;
    character->position = malloc(sizeof(Position));
    character->position->x = x;
    character->position->y = y;
    character->hitbox = malloc(sizeof(Hitbox));
    character->hitbox->origin = character->position;
    character->hitbox->height = height;
    character->hitbox->width = width;
    character->indexTexture = 0;
    character->isJumping = false;
    character->jumpHeight = -1;
    return character;
}

void addCharacterTexture(Character *character, char *textureName, char name[50]) {
    if (character->indexTexture < 10) {
        Texture *texture = getTexture(textureName);
        strcpy(character->characterTexture[character->indexTexture].name, name);
        character->characterTexture[character->indexTexture].textureId = texture->textureId;
        (character->indexTexture)++;
    }
}

GLuint getCharacterTexture(Character *character, char name[50]) {
    GLuint textureId = -1;
    
    for (int i = 0; i < character->indexTexture && textureId == -1; i++) {
        if (strcmp(character->characterTexture[i].name, name)) {
            textureId = character->characterTexture[i].textureId;
        }
    }

    return textureId;
}

void move(Character *character, int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT]) {
    // We get the position of Bubble to know where he is in the levelStructure
    //  The minus 4 is for the 4 bloc we always have on each side of the level
    //  The xLevelStructure need to be increase by 2 to avoid the 2 first bloc
    int xLevelStructure = 2 + (character->position->x / 45);
    //  The minus 2 is for the 2 bloc we always have at the top and the bottom of the level.
    //    The one at the top is not always display but we cannot stop Bubble at this position
    //    The yLevelStructure found is at the bottom of the array so, when we have are in 0 on the Y, we are in reality at the 23 or,
    //    when we are at the 5, we are at 23 - 5 = 18 and so on ...
    int yLevelStructure = (LEVEL_HEIGHT - 2) - (character->position->y / 54);

    switch (character->move) {
        case RIGHT:
            // We move the character to the right
            if (character->position->x + X_MOVEMENT < PLAY_WIDTH_SIZE)
                character->position->x += X_MOVEMENT;
            else
                character->position->x = PLAY_WIDTH_SIZE;
            break;
        case LEFT:
            // We move the character to the left
            if (character->position->x - X_MOVEMENT > 0)
                character->position->x -= X_MOVEMENT;
            else
                character->position->x = 0;
            break;
        case NONE:
            break;
    }

    if (character->isJumping) {
        if (character->jumpHeight < 0) {
            character->jumpHeight = character->position->y + JUMP_HEIGHT;
        }

        if (character->position->y < character->jumpHeight) {
            character->position->y += Y_MOVEMENT;
        } else {
            character->jumpHeight = -1;
            character->isJumping = false;
        }
    } else {
        // If the character is not jumping, we need to check if we are 
        //   on a solid zone
        int bloc = levelStructure[xLevelStructure][yLevelStructure];

        if (bloc == 0) {
            if (character->position->y - Y_MOVEMENT >= 0) {
                character->position->y -= Y_MOVEMENT;
            } else {
                character->position->y = 0;
            }
        }
    }
}