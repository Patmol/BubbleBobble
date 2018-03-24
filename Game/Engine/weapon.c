#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#include "texture.h"
#include "character.h"
#include "weapon.h"

//! Set the bullet use by the character
/*!
  \param character is a pointer to a character.
  \param textureName is a constant charater pointer.
  \param height is an integer for the height of the bullet hitbox
  \param width is an integer for the height of the bullet width
*/
void setBullet(Character *character, char *textureName, int height, int width, float speed) {
    Bullet *bullet = malloc(sizeof(Bullet));
    Texture *texture = getTexture(textureName);
    bullet->textureId = texture->textureId;
    bullet->position = malloc(sizeof(Position));
    bullet->position->x = 0;
    bullet->position->y = 0;
    bullet->hitbox = malloc(sizeof(Hitbox));
    bullet->hitbox->height = height * 1.5;
    bullet->hitbox->width = width * 1.5;
    bullet->hitbox->origin = bullet->position;
    bullet->speed = speed;
    character->bullet = bullet;
} 
//! Make the character shot a bullet
/*!
  \param character is a pointer to a character.
*/
Bullet* shot(Character *character) {
    Bullet *bullet = malloc(sizeof(Bullet));
    bullet->textureId = character->bullet->textureId;
    bullet->position = malloc(sizeof(Position));
    if (character->move == RIGHT || (character->move == NONE && character->prevMove == RIGHT)) {
        // If the character move to the right, we need to have a start position on x on the right of the character
        bullet->position->x = character->position->x + character->hitbox->width;
        bullet->move = RIGHT;
    } else {
        // Otherwise, we need to start of the left of the character
        bullet->position->x = character->position->x - character->bullet->hitbox->width;
        bullet->move = LEFT;
    }
    bullet->position->y = character->position->y + (character->hitbox->height / 3);
    bullet->hitbox = malloc(sizeof(Hitbox));
    bullet->hitbox->height = character->bullet->hitbox->height; 
    bullet->hitbox->width = character->bullet->hitbox->width;
    bullet->hitbox->origin = character->position;
    bullet->speed = character->bullet->speed;
    return bullet;
}
//! Make a bullet move
/*!
  \param the bullet to move
*/
void moveBullet(Bullet* bullet) {
    if (bullet->move == RIGHT) {
        bullet->position->x += bullet->speed;
    } else {
        bullet->position->x -= bullet->speed;
    }
}