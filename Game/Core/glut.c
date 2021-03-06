#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "home.h"
#include "game.h"
#include "glut.h"
#include "end_game.h"
#include "../Engine/texture.h"

/**************************************************************************/
/******************************* VARIABLES ********************************/
/**************************************************************************/
//! The state of the game
enum gameState state = LOGO;

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Initalize all data require for the game
void init(void) {
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // We need to load all textures of the application at the initialisation
    loadTextures("data/images.txt");
    // Initialize the logo data
    initLogo();
    // Initialize the home data
    initHome();
    // Initialize the controls data
    initControls();
    // Initialize the end game data
    initEndGame();
}
//! Function call by GLUT to display the screen
void display(void) {
    switch (state) {
        case GAME_1_PLAYER:
        case GAME_2_PLAYER:
            displayGame();
            break;
        case HELP:
            displayControls();
            break;
        case HOME:
            displayHome();
            break;
        case LOGO:
            displayLogo();
            break;
        case SCORE:
            break;
        case END_GAME_WIN:
            displayEndGame(true);
            clearGameInformation();
            break;
        case END_GAME_LOSE:
            displayEndGame(false);
            clearGameInformation();
            break;
    }
}
//! Function call by GLUT every X secondes 
void timer(int value) {
    switch (state) {
        case GAME_1_PLAYER:
        case GAME_2_PLAYER:
            timerGame();
            break;
        case HELP:
            break;
        case HOME:
            timerHome();
            break;
        case LOGO:
            timerLogo();
            break;
        case SCORE:
            break;
        case END_GAME_WIN:
        case END_GAME_LOSE:
            break;
    }
    glutPostRedisplay();
    glutTimerFunc(TIMER, timer, 0);
}
//! Function call by GLUT every X secondes (use with a longer timer)
void longTimer(int value) {
    switch (state) {
        case GAME_1_PLAYER:
        case GAME_2_PLAYER:
            longTimerGame();
            break;
        case HELP:
            break;
        case HOME:
            break;
        case LOGO:
            break;
        case SCORE:
            break;
        case END_GAME_WIN:
        case END_GAME_LOSE:
            break;
    }
    glutPostRedisplay();
    glutTimerFunc(LONG_TIMER, longTimer, 0);
}
//! Function call by GLUT every X secondes (use with a score timer)
void longerTimer(int value) {
    switch (state) {
        case GAME_1_PLAYER:
        case GAME_2_PLAYER:
            scoreTimerGame();
            break;
        case HELP:
            break;
        case HOME:
            break;
        case LOGO:
            timerEnterText();
            break;
        case SCORE:
            break;
        case END_GAME_WIN:
        case END_GAME_LOSE:
            break;
    }
    glutPostRedisplay();
    glutTimerFunc(SCORE_TIMER, longerTimer, 0);
}
//! Function call by GLUT every X secondes (use with to pop the ennemi)
void ennemyTimer(int value) {
    switch (state) {
        case GAME_1_PLAYER:
        case GAME_2_PLAYER:
            popEnnemiTimerGame();
            break;
        case HELP:
            break;
        case HOME:
            break;
        case LOGO:
            break;
        case SCORE:
            break;
        case END_GAME_WIN:
        case END_GAME_LOSE:
            break;
    }
    glutPostRedisplay();
    glutTimerFunc(ENNEMI_POP_TIMER, ennemyTimer, 0);
}
//! Function call by GLUT when the window is resize
void reshape(int w, int h) {
    if (h == 0) {
        h = 1;
    }
    
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, w/(GLdouble)h, 0.1, 1000.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glutPostRedisplay();
}
//! Function call by GLUT to handle the keyboard when a key is press
void keyboard(unsigned char key, int x, int y) {
    /* Escape */
    if (key == 27) {
        exit(0);
    }

    switch (state) {
        case GAME_1_PLAYER:
        case GAME_2_PLAYER:
            keyboardGame(key);
            break;
        case HELP:
            keyboardControls(key);
            break;
        case HOME:
            keyboardHome(key);
            break;
        case LOGO:
            // Carriage return
            if (key == 13) {
                state = HOME;
            }
            break;
        case SCORE:
            break;
        case END_GAME_WIN:
        case END_GAME_LOSE:
            keyboardEndGame(key);
            break;
    }
}
//! Function call by GLUT to handle the keyboard when a key is release
void keyboardUp(unsigned char key, int x, int y) {
    switch (state) {
        case GAME_1_PLAYER:
        case GAME_2_PLAYER:
            keyboardUpGame(key);
            break;
        case HELP:
            break;
        case HOME:
            break;
        case LOGO:
            break;
        case SCORE:
            break;
        case END_GAME_WIN:
        case END_GAME_LOSE:
            break;
    }
}
//! Handle the special keys
void specialInput(int key, int x, int y) {
    switch (state) {
        case GAME_1_PLAYER:
        case GAME_2_PLAYER:
            specialInputGame(key, x, y);
            break;
        case HELP:
            break;
        case HOME:
            specialInputHome(key, x, y);
            break;
        case LOGO:
            break;
        case SCORE:
            break;
        case END_GAME_WIN:
        case END_GAME_LOSE:
            break;
    }
}
//! Handle the special keys
void specialInputUp(int key, int x, int y) {
    switch (state) {
        case GAME_1_PLAYER:
        case GAME_2_PLAYER:
            specialInputUpGame(key, x, y);
            break;
        case HELP:
            break;
        case HOME:
            break;
        case LOGO:
            break;
        case SCORE:
            break;
        case END_GAME_WIN:
        case END_GAME_LOSE:
            break;
    }
}
//! Function to change the state of the game
void changeGameStatus(enum gameState newState) {
    state = newState;

    if (state == GAME_1_PLAYER || GAME_2_PLAYER) {
        // Initialize the data for the game
        initGame(1);
        setNumberOfPlayer(state == GAME_1_PLAYER ? 1: 2);
    }
}