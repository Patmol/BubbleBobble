#include <stdbool.h>

#ifndef _GLUT_H_
#define _GLUT_H_

#define TIMER 10
#define LONG_TIMER 40
#define WINDOW_WIDTH 800
#define WINDOW_HEIGH 600

/**************************************************************************/
/********************************** ENUM **********************************/
/**************************************************************************/
//! The different states of the game
enum gameState { GAME, HELP, HOME, LOGO, SCORE, END_GAME_WIN, END_GAME_LOSE  };

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
//! Function call by GLUT when the window is resize
void reshape(int w, int h);
//! Function call by GLUT to handle the keyboard when a key is press
void keyboard(unsigned char key, int x, int y);
//! Function call by GLUT to handle the keyboard when a key is release
void keyboardUp(unsigned char key, int x, int y);
//! Function to change the state of the game
void changeGameStatus(enum gameState newState);

#endif