#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "home.h"
#include "glut.h"
#include "../Engine/texture.h"

#define LOGO_Y_TRANSLATION 0.03

/**************************************************************************/
/********************************** ENUM **********************************/
/**************************************************************************/
//! The different states of the game
enum menu { PLAY, QUIT  };

/**************************************************************************/
/******************************* VARIABLES ********************************/
/**************************************************************************/
//! The texture of the logo
Texture* logo = NULL;
//! The texture of the play button
Texture* play = NULL;
//! The texture of the play button when selected
Texture* playSelected = NULL;
//! The texture of the quit button
Texture* quit = NULL;
//! The texture of the quit button when selected
Texture* quitSelected = NULL;
//! The Y position for the logo
float logoYPosition = 2.5f;
//! The selected menu
enum menu selectedMenu;

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Initialiaze the data for the logo screen
void initLogo() {
    // Load the texture of the logo
    logo = getTexture("logo");
}
//! Display the logo screen
void displayLogo() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    // Display the logo
    glBindTexture(GL_TEXTURE_2D, logo->textureId);
    glTranslatef(0.0, logoYPosition, -3.5);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -0.6f, 0.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -0.6f, 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 0.6f, 0.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 0.6f, 0.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}
//! Timer function to handle update of the logo screen
void timerLogo() {
    // Move the logo down to create the logo animation on the first screen
    if (logoYPosition > 0.4f) {
        logoYPosition -= LOGO_Y_TRANSLATION;
    }
}
//! Initialiaze the data for the home screen
void initHome() {
    // Load the texture of the play button
    play = getTexture("play");
    // Load the texture of the play selected button
    playSelected = getTexture("play-selected");
    // Load the texture of the quit button
    quit = getTexture("quit");
    // Load the texture of the quit selected button
    quitSelected = getTexture("quit-selected");
}
//! Display the home screen
void displayHome() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    // Display the logo
    glBindTexture(GL_TEXTURE_2D, logo->textureId);
    glPushMatrix();
    glTranslatef(0.0, 1.0f, -5.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -0.6f, 0.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -0.6f, 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 0.6f, 0.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 0.6f, 0.0f);
    glEnd();
    glPopMatrix();

    // Display the play button
    selectedMenu == PLAY ? glBindTexture(GL_TEXTURE_2D, playSelected->textureId) : glBindTexture(GL_TEXTURE_2D, play->textureId);
    glPushMatrix();
    glTranslatef(0.0, 0.0f, -8.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -0.2f, 0.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -0.2f, 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 0.2f, 0.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 0.2f, 0.0f);
    glEnd();
    glPopMatrix();

    // Display the quit button
    selectedMenu == QUIT ? glBindTexture(GL_TEXTURE_2D, quitSelected->textureId) : glBindTexture(GL_TEXTURE_2D, quit->textureId);
    glPushMatrix();
    glTranslatef(0.0, -0.5f, -8.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -0.2f, 0.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -0.2f, 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 0.2f, 0.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 0.2f, 0.0f);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}
//! Timer function to handle update of the home screen
void timerHome() {
}
//! Handle when a key is press on the keyboard.
/*!
  \param key an unsigned character
*/
void keyboardHome(unsigned char key) {
    switch (key) {
        case 13:
            switch (selectedMenu) {
                case PLAY:
                    changeGameStatus(GAME);
                    break;
                case QUIT:
                    exit(0);
                    break;
            }
            break;
        case 'z':
            if (selectedMenu > 0) {
                selectedMenu--;
            } else {
                selectedMenu = 0;
            }
            break;
        case 's':
        if (selectedMenu < 1) {
                selectedMenu++;
            } else {
                selectedMenu = 1;
            }
            break;
    }
}