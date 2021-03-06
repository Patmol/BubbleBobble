#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdbool.h>

#include "texture.h"
#include "hitbox.h"

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#define LEVEL_WIDTH 32            //! The number of bloc on the width
#define LEVEL_HEIGHT 25           //! The number of bloc on the height
#define PLAY_WIDTH_SIZE 1260      //! The width size of the screen game
#define PLAY_HEIGHT_SIZE 880      //! The height size of the screen game
#define CHARACTER_LIFE 100          //! The life of the character

/**************************************************************************/
/************************* STRUCTURES DEFINITIONS *************************/
/**************************************************************************/
//! Enumeration of the available movement.
typedef enum movement {
    NONE,               /*!< The character doesn't move. */ 
    LEFT,               /*!< The character is moving to the left. */ 
    RIGHT               /*!< The character is moving to the right. */ 
} Movement;

//! The structure for a texture used by a character.
typedef struct characterTexture {
    char name[50];      /*!< The name of the texture used to identify the texture */
    GLuint textureId;   /*!< The OpenGL texture identifiant. */
} CharacterTexture;

//! The structure for a bullet shot by the character
typedef struct bullet {
    GLuint textureId;   /*!< The texture of the bullet */
    Position *position; /*!< The position of the bullet in the space (at the bottom left). */
    Hitbox *hitbox;     /*!< The hitbox of the bullet. */
    Movement move;      /*!< The movement of the bullet */
    float speed;        /*!< The speed of the bullet */
    int dammage;        /*!< The dammage of the bullet */
} Bullet;

//! The structure for a character.
typedef struct character {
    char name[100];             /*!< The name of the character. */
    int life;                   /*!< The life of the character */
    int speed;                  /*!< The speed of the character */
    int fallSpeed;              /*!< The fall speed of the character */
    Position *position;         /*!< The position of the character in the space (at the bottom left). */
    Hitbox *hitbox;             /*!< The hitbox of the character. */
    Movement move;              /*!< The movement of the character. */
    Movement prevMove;          /*!< The previous movement of the character. */
    int indexTexture;           /*!< The index (for the characterTexture array) of the texture used to display the character. */
    float jumpHeight;           /*!< The maximum height of the jump. */
    bool isJumping;             /*!< If the character is jumping or not. */
    CharacterTexture characterTexture[10];  /*!< An array contening all textures of the character */
    Bullet *bullet;              /*< The bullet use by the character */
} Character;

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
Character *initializeCharacter(char *name, int speed, int fallSpeed, float x, float y, float height, float width);
//! Add a texture to a character.
/*!
  \param character is a pointer to a character.
  \param textureName is a constant charater pointer.
  \param name is an array (50) of character.
*/ 
void addCharacterTexture(Character *character, char *textureName, char name[50]);
//! Get the texture ID of a character.
/*!
  \param character is a pointer to a character.
  \param name is an array (50) of character.
  \return The texture ID for the name wanted.
*/
GLuint getCharacterTexture(Character *character, char name[50]);
//! Make a character move from one position to an other.
/*!
  \param character is a pointer to a character.
  \param levelStructure is a 2D array (LEVEL_WIDTH/LEVEL_HEIGHT)
*/
void moveCharacter(Character *character, int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT]);
//! Make a character jump.
/*!
  \param character is a pointer to a character.
  \param levelStructure is a 2D array (LEVEL_WIDTH/LEVEL_HEIGHT)
*/
void jumpCharacter(Character *character, int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT]);
//! Get the position of the groun under the character.
/*!
  \param character is a pointer to a character.
  \param levelStructure is a 2D array (LEVEL_WIDTH/LEVEL_HEIGHT)
  \return The position of the ground
*/
Position getCharacterGround(Character *character, int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT]);
//! Get the X level character position in the structure.
/*
  \param character is a pointer to a character.
  \return the X level character position in the structure.
*/
int getXLevelStructureCharacterPosition(Character *character);
//! Get the Y level character position in the structure.
/*
  \param character is a pointer to a character.
  \return the Y level character position in the structure.
*/
int getYLevelStructureCharacterPosition(Character *character);
//! Get the Y ground position.
/*
  \param an integer position
  \return the Y ground position.
*/
int getYGroundPosition(int position);
//! Clear the character data 
void clearCharacter(Character* character);

#endif