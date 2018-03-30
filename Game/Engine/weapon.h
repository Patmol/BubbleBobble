#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "texture.h"
#include "character.h"

#ifndef _WEAPON_H_
#define _WEAPON_H_

//! Set the bullet use by the character
/*!
  \param character is a pointer to a character.
  \param textureName is a constant charater pointer.
  \param height is an integer for the height of the bullet hitbox.
  \param width is an integer for the height of the bullet width.
*/
void setBullet(Character *character, char *textureName, int height, int width, float speed, int dammage);
//! Make the character shot a bullet
/*!
  \param character is a pointer to a character.
*/
Bullet* shot(Character *character);
//! Make a bullet move
/*!
  \param the bullet to move
*/
void moveBullet(Bullet* bullet);
#endif