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
enum menu { 
    PLAY_MENU,          /*!< The play menu is selected */
    HELP_MENU,          /*!< The help menu is selected */
    QUIT_MENU           /*!< The quit menu is selected */
};

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Go up in the menu selection
void menuSelectionUp();
//! Go down in the menu selection
void menuSelectionDown();

/**************************************************************************/
/******************************* VARIABLES ********************************/
/**************************************************************************/
//! The texture of the logo
Texture* logo = NULL;
//! The texture of the enter text
Texture* enter = NULL;
//! The texture of the play button
Texture* play = NULL;
//! The texture of the controls texrt
Texture* controls = NULL;
//! The texture of the play button when selected
Texture* playSelected = NULL;
//! The texture of the quit button
Texture* quit = NULL;
//! The texture of the quit button when selected
Texture* quitSelected = NULL;
//! The texture of the help button
Texture* help = NULL;
//! The texture of the help button when selected
Texture* helpSelected = NULL;
//! The texture of the score button
Texture* score = NULL;
//! The texture of the score button when selected
Texture* scoreSelected = NULL;

//! The Y position for the logo
float logoYPosition = 2.5f;
//! The selected menu
enum menu selectedMenu;
//! Display the ENTER text
bool displayEnter = true;

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Initialiaze the data for the logo screen
void initLogo() {
    // Load the texture of the logo
    logo = getTexture("logo");
    // Load the texture of the logo
    enter = getTexture("enter");
}
//! Display the logo screen
void displayLogo() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    // Display the logo
    glBindTexture(GL_TEXTURE_2D, logo->textureId);
    glPushMatrix();
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
    glPopMatrix();

    // Display the enter text
    if (displayEnter) {
        glBindTexture(GL_TEXTURE_2D, enter->textureId); 
        glPushMatrix();
        glTranslatef(0.0, -1.0f, -8.0f);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-1.0f, -0.15f, 0.0f);

            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(1.0f, -0.15f, 0.0f);

            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(1.0f, 0.15f, 0.0f);

            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-1.0f, 0.15f, 0.0f);
        glEnd();
        glPopMatrix();
    }

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
//! Timer function to handle update of the display of the enter text
void timerEnterText() {
    displayEnter = !displayEnter;
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
    // Load the texture of the help button
    help = getTexture("help");
    // Load the texture of the help selected button
    helpSelected = getTexture("help-selected");
    // Load the texture of the score button
    score = getTexture("score");
    // Load the texture of the score selected button
    scoreSelected = getTexture("score-selected");
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
    selectedMenu == PLAY_MENU ? glBindTexture(GL_TEXTURE_2D, playSelected->textureId) : glBindTexture(GL_TEXTURE_2D, play->textureId);
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

    // Display the help button
    selectedMenu == HELP_MENU ? glBindTexture(GL_TEXTURE_2D, helpSelected->textureId) : glBindTexture(GL_TEXTURE_2D, help->textureId);
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

    // Display the quit button
    selectedMenu == QUIT_MENU ? glBindTexture(GL_TEXTURE_2D, quitSelected->textureId) : glBindTexture(GL_TEXTURE_2D, quit->textureId);
    glPushMatrix();
    glTranslatef(0.0, -1.0f, -8.0f);
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
                case PLAY_MENU:
                    changeGameStatus(GAME);
                    break;
                case HELP_MENU:
                    changeGameStatus(HELP);
                    break;
                case QUIT_MENU:
                    exit(0);
                    break;
            }
            break;
        case 'z':
            menuSelectionUp();
            break;
        case 's':
            menuSelectionDown();
            break;
    }
}
//! Handle the special keys
void specialInputHome(int key, int x, int y) {
    switch(key)
    {
        case GLUT_KEY_UP:
            menuSelectionUp();
            break;
        case GLUT_KEY_DOWN:
            menuSelectionDown();
            break;
    }
}
//! Initialiaze the data for the controls screen
void initControls() {
    // Load the texture of the controls
    controls = getTexture("controls");
}
//! Display the controls screen
void displayControls() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    // Display the controls
    glBindTexture(GL_TEXTURE_2D, controls->textureId);
    glTranslatef(0.0f, 0.0f, -3.5f);

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
//! Handle when a key is press on the keyboard.
/*!
  \param key an unsigned character
*/
void keyboardControls(unsigned char key) {
    switch (key) {
        case 13:
            changeGameStatus(HOME);
            break;
    }
}
//! Go up in the menu selection
void menuSelectionUp() {
    if (selectedMenu > 0) {
        selectedMenu--;
    } else {
        selectedMenu = 0;
    }
}
//! Go down in the menu selection
void menuSelectionDown() {
    if (selectedMenu < 2) {
        selectedMenu++;
    } else {
        selectedMenu = 2;
    }
}