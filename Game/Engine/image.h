#ifndef _GLUT_H_
#define _GLUT_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLuint LoadTexture(char *filename);

#endif