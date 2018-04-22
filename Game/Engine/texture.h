#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef _DATA_H_
#define _DATA_H_

/**************************************************************************/
/************************* STRUCTURES DEFINITIONS *************************/
/**************************************************************************/
//! The structure for a texture.
typedef struct texture {
    char filename[100];             /*!< The name of the file. */
    char name[40];                  /*!< The name of the texture. */
    GLuint textureId;               /*!< The texture ID use by OpenGL. */
    struct texture *next;           /*!< The next texture in the list. */ 
} Texture;

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Load all the textures used by the application
/*
  \param sourcesPath: path to the file with the path to the textures
*/
void loadTextures(char*);
//! Get a specific texture
/*
  \param name the name of the texture to get
  \return the texture structure
*/
Texture* getTexture(char*);

#endif