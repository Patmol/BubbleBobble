#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdbool.h>

#include "texture.h"
#include "hitbox.h"

#ifndef _ITEM_H_
#define _ITEM_H_

/**************************************************************************/
/************************* STRUCTURES DEFINITIONS *************************/
/**************************************************************************/
typedef struct item {
    int textureId;              /*!< The texture identifier used to display the item. */
    int scoreValue;             /*!< The score of the item. */
    int lifetime;               /*!< The number of turn the item stay */
    Position *position;         /*!< The position of the item in the space (at the bottom left). */
    Hitbox *hitbox;             /*!< The hitbox of the character. */
} Item;

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Initialize an item
/*!
  \param textureName is a constant charater pointer.
  \param scoreValue is the score of the item.
  \param x is an integer argument for the position.
  \param y is an integer argument for the position.
  \param height is an integer argument for the hitbox height.
  \param width is an integer argument for the hitbox width.
*/
Item *initializeItem(char *textureName, int scoreValue, float x, float y, float height, float width);
//! We clear the item memory data
void clearItem(Item* item);

#endif