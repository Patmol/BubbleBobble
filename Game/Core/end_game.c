#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdbool.h>

#include "../Engine/texture.h"

/**************************************************************************/
/******************************* VARIABLES ********************************/
/**************************************************************************/
//! The texture of the end game when the player win
Texture* endGameLogoWin = NULL;
//! The texture of the end game when the player lose
Texture* endGameLogoLose = NULL;

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Initialize the end of the game
void initEndGame() {
    endGameLogoWin = getTexture("logo");
    endGameLogoLose = getTexture("logo");
}
//! Display the end of the game
/*!
  \param a boolean
*/
void displayEndGame(bool win) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    // Bind the texture depending if the player win or not
    if (win) {
        glBindTexture(GL_TEXTURE_2D, endGameLogoWin->textureId);
    } else {
        glBindTexture(GL_TEXTURE_2D, endGameLogoLose->textureId);
    }
    
    // Display the logo
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