#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifndef _TGA_H_
#define _TGA_H_

GLuint loadTGATexture(char filename[]);

#endif