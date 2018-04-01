#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdbool.h>

#include "../Engine/texture.h"

Texture* endGameLogoWin = NULL;
Texture* endGameLogoLose = NULL;

void initEndGame() {
    endGameLogoWin = getTexture("logo");
    endGameLogoLose = getTexture("logo");
}
void displayEndGame(bool win) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    // Display the logo
    if (win) {
        glBindTexture(GL_TEXTURE_2D, endGameLogoWin->textureId);
    } else {
        glBindTexture(GL_TEXTURE_2D, endGameLogoLose->textureId);
    }
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -10.0f);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-3.0f, -2.4f, 0.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(3.0f, -2.4f, 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(3.0f, 2.4f, 0.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-3.0f, 2.4f, 0.0f);
    glEnd();
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}