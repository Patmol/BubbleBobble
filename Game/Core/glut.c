#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "glut.h"
#include "../Engine/texture.h"
#include "home.h"

Texture* textures;

void init(void) {
    // We need to load all textures of the application at the initialisation
    textures = loadTextures("datas/images.txt");
    initHome(textures);
}

void display(void) {
    displayHome();
}

void timer(int value) {
    timerHome();
    glutPostRedisplay();
    glutTimerFunc(TIMER, timer, 0);
}

void reshape(int w, int h) {
    if (h == 0) {
        h = 1;
    }
    
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (45.0, w/(GLdouble)h, 0.1, 1000.0);
    
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    
    glutPostRedisplay ();
}