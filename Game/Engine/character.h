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

//! Enumeration of the available movement.
typedef enum movement {
    NONE,               /*!< The character doesn't move. */ 
    LEFT,               /*!< The character is moving to the left. */ 
    RIGHT               /*!< The character is moving to the right. */ 
} Movement;

//! The structure for a position in a 2D space.
typedef struct position {
    float x;            /*!< The position on the horizontal axe. */
    float y;            /*!< The position on the vertical axe. */
} Position;

//! The structure for a hitbox.
typedef struct hitbox {
    float height;       /*!< The height of the hitbox. */
    float width;        /*!< The width of the hitbox. */
    Position *origin;   /*!< The orgion position of the hitbox. */
} Hitbox;

//! The structure for a texture used by a character.
typedef struct characterTexture {
    char name[50];      /*!< The name of the texture used to identify the texture */
    GLuint textureId;   /*!< The OpenGL texture identifiant. */
} CharacterTexture;

//! The structure for a character.
typedef struct character {
    char name[100];             /*!< The name of the character. */
    int life;                   /*!< The life of the character */
    Position *position;         /*!< The position of the character in the space (at the bottom left). */
    Hitbox *hitbox;             /*!< The hitbox of the character. */
    Movement move;              /*!< The movement of the character. */
    Movement prevMove;          /*!< The previous movement of the character. */
    int indexTexture;           /*!< The index (for the characterTexture array) of the texture used to display the character. */
    float jumpHeight;           /*!< The maximum height of the jump. */
    bool isJumping;             /*!< If the character is jumping or not. */
    CharacterTexture characterTexture[10];  /*!< An array contening all textures of the character */
    GLuint bulletTextureId;     /*!< The texture identifier for the bullet */  
} Character;

//! Initialize a character.
/*!
  \param name is a constant character pointer.
  \param x is an integer argument for the position.
  \param y is an integer argument for the position.
  \param height is an integer argument for the hitbox height.
  \param width is an integer argument for the hitbox width.
  \return The character
*/
Character *initializeCharacter(char *name, float x, float y, float height, float width);

//! Add a texture to a character.
/*!
  \param character is a pointer to a character.
  \param textureName is a constant charater pointer.
  \param name is an array (50) of character.
*/ 
void addCharacterTexture(Character *character, char *textureName, char name[50]);

//! Set the texture of the weapon.
/*!
  \param character is a pointer to a character.
  \param textureName is a constant charater pointer.
*/
void setBulletTexture(Character *character, char *textureName);

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
void move(Character *character, int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT]);

//! Make a character jump.
/*!
  \param character is a pointer to a character.
  \param levelStructure is a 2D array (LEVEL_WIDTH/LEVEL_HEIGHT)
*/
void jump(Character *character, int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT]);

//! Get the position of the groun under the character.
/*!
  \param character is a pointer to a character.
  \param levelStructure is a 2D array (LEVEL_WIDTH/LEVEL_HEIGHT)
  \return The position of the ground
*/
Position getCharacterGround(Character *character, int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT]);

int getXLevelStructureCharacterPosition(Character *character);
int getYLevelStructureCharacterPosition(Character *character);
int getYGroundPosition(int position);

#endif