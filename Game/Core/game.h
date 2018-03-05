#include "../Engine/texture.h"

#ifndef _HOME_H_
#define _HOME_H_

/*
 * Functions used for the displaying of the game
 */
void initGame(int);
void displayGame();
void timerGame();
void keyboardGame(unsigned char key);

#endif

void loadLevel(int);