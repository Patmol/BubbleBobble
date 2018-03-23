#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "texture.h"
#include "character.h"

#ifndef _WEAPON_H_
#define _WEAPON_H_

//! The structure for a bullet shot by the character
typedef struct bullet {
    GLuint textureId;   /*!< The texture of the bullet */
    Position *position; /*!< The position of the bullet in the space (at the bottom left). */
    Hitbox *hitbox;     /*!< The hitbox of the bullet. */
} Bullet;

Bullet* shot(Character *character);

#endif