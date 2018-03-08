#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <string.h>

#include "texture.h"
#include "character.h"

Character *initializeCharacter(char *name, float x, float y, float height, float width) {
    Character *character = malloc(sizeof(Character));
    strcpy(character->name, name);
    character->life = 100;
    character->move = RIGHT;
    character->position = malloc(sizeof(Position));
    character->position->x = x;
    character->position->y = y;
    character->hitbox = malloc(sizeof(Hitbox));
    character->hitbox->origin = character->position;
    character->hitbox->height = height;
    character->hitbox->width = width;
    character->indexTexture = 0;
    return character;
}

void addCharacterTexture(Character *character, char *textureName, char name[50]) {
    if (character->indexTexture < 10) {
        Texture *texture = getTexture(textureName);
        strcpy(character->characterTexture[character->indexTexture].name, name);
        character->characterTexture[character->indexTexture].textureId = texture->textureId;
        (character->indexTexture)++;
    }
}

GLuint getCharacterTexture(Character *character, char name[50]) {
    GLuint textureId = -1;
    
    for (int i = 0; i < character->indexTexture && textureId == -1; i++) {
        if (strcmp(character->characterTexture[i].name, name)) {
            textureId = character->characterTexture[i].textureId;
        }
    }

    return textureId;
}