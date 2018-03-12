#include "../Engine/texture.h"
#include "../Engine/character.h"

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
void keyboardUpGame(unsigned char key);

void characterDisplay(Character *character, GLuint textureId);

#endif