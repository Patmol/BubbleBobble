#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef _DATA_H_
#define _DATA_H_

typedef struct texture {
    // The name of the file
    char filename[100];
    // The name of the texture
    char name[40];
    // The texture ID use by OpenGL
    GLuint textureId;
    // The next texture in the list
    struct texture *next;
} Texture;

// Load all the textures used by the application
void loadTextures(char*);
// Get a specific texture
Texture* getTexture(char*);

#endif