#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <string.h>

#include "texture.h"
#include "character.h"

Character *initializeCharacter(char *name, float x, float y, float height, float width, char *textureName) {
    Character *character = malloc(sizeof(Character));
    strcpy(character->name, name);
    character->position = malloc(sizeof(Position));
    character->position->x = x;
    character->position->y = y;
    character->hitbox = malloc(sizeof(Hitbox));
    character->hitbox->origin = character->position;
    character->hitbox->height = height;
    character->hitbox->width = width;
    character->textureId = getTexture(textureName)->textureId;
    return character;
}