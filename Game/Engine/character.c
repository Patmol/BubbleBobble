#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "texture.h"
#include "character.h"
#include "weapon.h"

#define JUMP_HEIGHT 350             //! The jump height of a character
#define POSITION_TRANSFORM 45       //! The position transform

/**************************************************************************/
/******************************* VARIABLES ********************************/
/**************************************************************************/
//! The start position when the player jump
int startJump = 0;

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Initialize a character.
/*!
  \param name is a constant character pointer.
  \param speed is an integer for the speed of the character.
  \param fallSpeed is an integer for the speed of the character.
  \param x is an integer argument for the position.
  \param y is an integer argument for the position.
  \param height is an integer argument for the hitbox height.
  \param width is an integer argument for the hitbox width.
  \return The character
*/
Character *initializeCharacter(char *name, int speed, int fallSpeed, float x, float y, float height, float width) {
    Character *character = malloc(sizeof(Character));
    strcpy(character->name, name);
    character->life = CHARACTER_LIFE;
    character->speed = speed;
    character->fallSpeed = fallSpeed;
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
//! Add a texture to a character.
/*!
  \param character is a pointer to a character.
  \param textureName is a constant charater pointer.
  \param name is an array (50) of character.
*/ 
void addCharacterTexture(Character *character, char *textureName, char name[50]) {
    if (character->indexTexture < 10) {
        Texture *texture = getTexture(textureName);
        strcpy(character->characterTexture[character->indexTexture].name, name);
        character->characterTexture[character->indexTexture].textureId = texture->textureId;
        (character->indexTexture)++;
    }
}
//! Get the texture ID of a character.
/*!
  \param character is a pointer to a character.
  \param name is an array (50) of character.
  \return The texture ID for the name wanted.
*/
GLuint getCharacterTexture(Character *character, char name[50]) {
    GLuint textureId = -1;
    
    for (int i = 0; i < character->indexTexture && textureId == -1; i++) {
        if (strcmp(character->characterTexture[i].name, name)) {
            textureId = character->characterTexture[i].textureId;
        }
    }

    return textureId;
}
//! Make a character move from one position to an other.
/*!
  \param character is a pointer to a character.
  \param levelStructure is a 2D array (LEVEL_WIDTH/LEVEL_HEIGHT)
*/
void moveCharacter(Character *character, int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT]) {
    int yGroundPosition = 0;
    Position groundPosition;

    switch (character->move) {
        case RIGHT:
            // We move the character to the right
            if (character->position->x + character->speed < PLAY_WIDTH_SIZE)
                character->position->x += character->speed;
            else
                character->position->x = PLAY_WIDTH_SIZE;
            break;
        case LEFT:
            // We move the character to the left
            if (character->position->x - character->speed > 0)
                character->position->x -= character->speed;
            else
                character->position->x = 0;
            break;
        case NONE:
            break;
    }

    groundPosition = getCharacterGround(character, levelStructure);

    if (character->isJumping) {
        if (character->jumpHeight < 0) {
            character->jumpHeight = character->position->y + JUMP_HEIGHT;
        }

        if (character->position->y < character->jumpHeight) {
            character->position->y += character->fallSpeed;
        } else {
            character->isJumping = false;
        }
    } else {
        if (character->position->y - character->fallSpeed >= 0) {
            yGroundPosition = getYGroundPosition(groundPosition.y);

            if (character->position->y - character->fallSpeed <= yGroundPosition) {
                character->position->y = yGroundPosition;
                character->jumpHeight = -1;
            } else {
                character->position->y -= character->fallSpeed;
            }
        } else {
            character->position->y = 0;
        }
    }
}
//! Make a character jump.
/*!
  \param character is a pointer to a character.
  \param levelStructure is a 2D array (LEVEL_WIDTH/LEVEL_HEIGHT)
*/
void jumpCharacter(Character *character, int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT]) {
    int yLevelStructure = getYLevelStructureCharacterPosition(character);
    Position groundPosition = getCharacterGround(character, levelStructure);

    // We need to check for the yLevelStructure + 1 when the character is at the ground level
    //  and just yLevelStructure when the character is on a platform
    if (yLevelStructure + 1 == groundPosition.y || yLevelStructure == groundPosition.y) {
        character->isJumping = true;
    }
}
//! Get the position of the groun under the character.
/*!
  \param character is a pointer to a character.
  \param levelStructure is a 2D array (LEVEL_WIDTH/LEVEL_HEIGHT)
  \return The position of the ground
*/
Position getCharacterGround(Character *character, int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT]) {
    int xLevelStructure = getXLevelStructureCharacterPosition(character);
    int yLevelStructure = getYLevelStructureCharacterPosition(character);

    Position position;

    // We check if the x and y for the levelStructure are between our range
    if (xLevelStructure < 2) {
        xLevelStructure = 2;
    } else if (xLevelStructure > LEVEL_WIDTH - 4) {
        xLevelStructure = LEVEL_WIDTH - 4;
    }

    if (yLevelStructure < 1) {
        yLevelStructure = 1;
    } else if (yLevelStructure > LEVEL_HEIGHT - 2) {
        yLevelStructure = LEVEL_HEIGHT - 2;
    }

    position.x = xLevelStructure;
    position.y = -1;

    // We check on which y axe we have the first ground
    for (int i = yLevelStructure; i < LEVEL_HEIGHT && position.y == -1; i++) {
        if (levelStructure[xLevelStructure][i] == 1) {
            position.y = i;
        }
    }

    return position;
}
//! Get the X level character position in the structure.
/*
  \param character is a pointer to a character.
  \return the X level character position in the structure.
*/
int getXLevelStructureCharacterPosition(Character *character) {
    // We get the position of Bubble to know where he is in the levelStructure
    //  The minus 4 is for the 4 bloc we always have on each side of the level
    //  The xLevelStructure need to be increase by 2 to avoid the 2 first bloc
    return 2 + (character->position->x / POSITION_TRANSFORM);
}
//! Get the Y level character position in the structure.
/*
  \param character is a pointer to a character.
  \return the Y level character position in the structure.
*/
int getYLevelStructureCharacterPosition(Character *character) {
    //  The minus 2 is for the 2 bloc we always have at the top and the bottom of the level.
    //    The one at the top is not always display but we cannot stop Bubble at this position
    //    The yLevelStructure found is at the bottom of the array so, when we have are in 0 on the Y, we are in reality at the 23 or,
    //    when we are at the 5, we are at 23 - 5 = 18 and so on ...
    return (LEVEL_HEIGHT - 2) - (int)(character->position->y / POSITION_TRANSFORM);
}
//! Get the Y ground position.
/*
  \param an integer position
  \return the Y ground position.
*/
int getYGroundPosition(int yPosition) {
    return ((LEVEL_HEIGHT - 1 - yPosition) * (POSITION_TRANSFORM - 1));
}
//! Clear the character data 
void clearCharacter(Character* character) {
    if (character != NULL) {
        if (character->position != NULL) free(character->position);
        if (character->hitbox != NULL) free(character->hitbox);
        // TODO: Clean texture
        free(character->bullet);
        free(character);
    }
}