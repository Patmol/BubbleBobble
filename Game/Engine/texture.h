#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef _DATA_H_
#define _DATA_H_

typedef struct texture {
    char *name;
    char *filename;
    GLuint textureId;
} Texture;

typedef struct textures {
    struct texture *data;
    struct textures *next;
} Textures;

Textures* loadTextures(char* sourcesPath);

#endif