#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef _DATA_H_
#define _DATA_H_

typedef struct texture {
    char filename[100];
    char name[40];
    GLuint textureId;
    struct texture *next;
} Texture;

Texture* loadTextures(char* sourcesPath);

#endif