#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#include "texture.h"
#include "character.h"
#include "weapon.h"

Bullet* shot(Character *character) {
    Bullet *bullet = malloc(sizeof(Bullet));
    bullet->textureId = character->bulletTextureId;
    bullet->position = malloc(sizeof(Position));
    bullet->position->x = character->position->x;
    bullet->position->y = character->position->y;
    /* TODO: Add hitbox information */
    bullet->hitbox = malloc(sizeof(Hitbox));
    bullet->hitbox->height = 32; 
    bullet->hitbox->width = 38;
    return bullet;
}