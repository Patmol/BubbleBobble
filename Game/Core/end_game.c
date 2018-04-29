#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdbool.h>

#include "glut.h"
#include "../Engine/texture.h"

#define NUMBER_WIDTH 12                 //! The width of a number
#define NUMBER_HEIGHT 18                //! The height of a number
#define SCORE_HEIGHT_POSITION -300      //! The score height position 
#define SCORE_WIDTH_POSITION -100       //! The score width position 

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Display the logo
/*!
  \param a boolean
*/
void endLogoDisplay(bool win);
//! Display the score
void endScoreDisplay();

/**************************************************************************/
/******************************* VARIABLES ********************************/
/**************************************************************************/
//! The texture of the end game when the player win
Texture* endGameLogoWin = NULL;
//! The texture of the end game when the player lose
Texture* endGameLogoLose = NULL;
//! The score of the player
int playerScore;
//! The texture for the numbers
Texture* numbers[10];

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Initialize the end of the game
void initEndGame() {
    endGameLogoWin = getTexture("logo");
    endGameLogoLose = getTexture("logo");

    // Load numbers texture
    numbers[0] = getTexture("0");
    numbers[1] = getTexture("1");
    numbers[2] = getTexture("2");
    numbers[3] = getTexture("3");
    numbers[4] = getTexture("4");
    numbers[5] = getTexture("5");
    numbers[6] = getTexture("6");
    numbers[7] = getTexture("7");
    numbers[8] = getTexture("8");
    numbers[9] = getTexture("9");
}
//! Display the end of the game
/*!
  \param a boolean
*/
void displayEndGame(bool win) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    endScoreDisplay();
    endLogoDisplay(win);
    
    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}
//! Display the logo
/*!
  \param a boolean
*/
void endLogoDisplay(bool win) {
    // Bind the texture depending if the player win or not
    if (win) {
        glBindTexture(GL_TEXTURE_2D, endGameLogoWin->textureId);
    } else {
        glBindTexture(GL_TEXTURE_2D, endGameLogoLose->textureId);
    }

    glPushMatrix();
    glTranslatef(0.0f, 1.0f, -10.0f);

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
}
//! Display the score
void endScoreDisplay() {
    int currentScore = playerScore;
    for (int i = 0; i < 10; i++) {
        glBindTexture(GL_TEXTURE_2D, numbers[currentScore % 10]->textureId);
        currentScore /= 10;

        glPushMatrix();
        // We move to the position where we want to display our bloc
        glTranslatef(
            -((SCORE_WIDTH_POSITION + (NUMBER_WIDTH * 2) * i) / 146.0), 
            ((SCORE_HEIGHT_POSITION - (NUMBER_HEIGHT * 2)) / 146.0), 
            -10.0f);
        
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-((1.0/292.0) * (NUMBER_WIDTH * 2)), -((1.0/282.0) * (NUMBER_HEIGHT * 2)), 0.0f);
    
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(((1.0/292.0) * (NUMBER_WIDTH * 2)), -((1.0/282.0) * (NUMBER_HEIGHT * 2)), 0.0f);

            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(((1.0/292.0) * (NUMBER_WIDTH * 2)), ((1.0/282.0) * (NUMBER_HEIGHT * 2)), 0.0f);

            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-((1.0/292.0) * (NUMBER_WIDTH * 2)), ((1.0/282.0) * (NUMBER_HEIGHT * 2)), 0.0f);
        glEnd();
        glPopMatrix();
    }
}
//! Set the score of the player
/*
  \paran the score
*/
void setScore(int score) {
    playerScore = score;
}
//! Handle when a key is press on the keyboard.
/*!
  \param key an unsigned character
*/
void keyboardEndGame(unsigned char key) {
    switch (key) {
        case 13:
            changeGameStatus(HOME);
            break;
    }
}