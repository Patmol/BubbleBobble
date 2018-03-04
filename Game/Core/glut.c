#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "glut.h"
#include "../Engine/texture.h"

void init(void) {
    // We need to load all textures of the application at the initialisation
    loadTextures("/datas/images.txt");
}

void display(void) {
}

void reshape(int w, int h) {
}