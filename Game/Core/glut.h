#include <stdbool.h>

#ifndef _GLUT_H_
#define _GLUT_H_

#define TIMER 10
#define LONG_TIMER 40
#define SCORE_TIMER 500
#define ENNEMI_POP_TIMER 2000
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

/**************************************************************************/
/********************************** ENUM **********************************/
/**************************************************************************/
//! The different states of the game
enum gameState { 
    GAME_1_PLAYER,      /*!< The game screen for 1 player */
    GAME_2_PLAYER,      /*!< The game screen for 2 player */
    HELP,               /*!< The help screen */
    HOME,               /*!< The home screen */
    LOGO,               /*!< The logo screen */
    SCORE,              /*!< The score screen */
    END_GAME_WIN,       /*!< The end game with a win screen */
    END_GAME_LOSE       /*!< The end game with a lost screen */
};

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Initalize all data require for the game
void init(void);
//! Function call by GLUT to display the screen
void display(void);
//! Function call by GLUT every X secondes 
void timer(int value);
//! Function call by GLUT every X secondes (use with a longer timer)
void longTimer(int value);
//! Function call by GLUT every X secondes (use with a score timer)
void longerTimer(int value);
//! Function call by GLUT every X secondes (use with to pop the ennemi)
void ennemyTimer(int value);
//! Function call by GLUT when the window is resize
void reshape(int w, int h);
//! Function call by GLUT to handle the keyboard when a key is press
void keyboard(unsigned char key, int x, int y);
//! Function call by GLUT to handle the keyboard when a key is release
void keyboardUp(unsigned char key, int x, int y);
//! Handle the special keys
void specialInput(int key, int x, int y);
//! Handle the special keys
void specialInputUp(int key, int x, int y);
//! Function to change the state of the game
void changeGameStatus(enum gameState newState);

#endif