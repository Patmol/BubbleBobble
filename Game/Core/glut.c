#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "glut.h"
#include "../Engine/image.h"

static GLfloat spin = 0.0f;

void init(void) {
    glClearColor(75.0 / 255.0, 75.0 / 255.0, 75.0 / 255.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    // Image path must be set for the out file
    glBindTexture(GL_TEXTURE_2D, LoadTexture("images/bloc-level-1.bmp"));

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); 
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, 1); 
        glVertex3f(0, 100, 0);
        glTexCoord2f(1, 1); 
        glVertex3f(100, 100, 0);
        glTexCoord2f(1, 0); 
        glVertex3f(100, 0, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}