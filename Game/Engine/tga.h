#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifndef _TGA_H_
#define _TGA_H_

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Load a TGA texture
/*
  \param filename is a constant character pointer.
  \return a OpenGL uint
*/
GLuint loadTGATexture(char filename[]);

#endif