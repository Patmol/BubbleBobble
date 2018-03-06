#include "../Engine/texture.h"

#ifndef _HOME_H_
#define _HOME_H_

/*
 * Functions used for the displaying of the game
 */
// Initialiaze the data for the game screen
void initGame(int);
// Display the game screen
void displayGame();
// Timer function to handle update of the game screen
void timerGame();
// Handle the keyboard input
void keyboardGame(unsigned char key);

#endif

// Load a level (send in parameter) from a file
void loadLevel(int);