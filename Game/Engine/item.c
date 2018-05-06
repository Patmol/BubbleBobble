#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdbool.h>

#include "texture.h"
#include "hitbox.h"
#include "item.h"

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
Item *initializeItem(char *textureName, int scoreValue, float x, float y, float height, float width) {
    Item *item = malloc(sizeof(Item));
    Texture *texture = getTexture(textureName);
    item->scoreValue = scoreValue;
    item->position = malloc(sizeof(Position));
    item->position->x = x;
    item->position->y = y;
    item->hitbox = malloc(sizeof(Hitbox));
    item->hitbox->origin = item->position;
    item->hitbox->height = height;
    item->hitbox->width = width;
    item->textureId = texture->textureId;
    item->life = 200;
    return item;
}
//! We clear the item memory data
void clearItem(Item* item) {
  if (item != NULL) {
    if (item->position != NULL) free(item->position);
    if (item->hitbox != NULL) free(item->hitbox);
    free(item);
  }
}