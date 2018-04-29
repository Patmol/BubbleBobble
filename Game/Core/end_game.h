#ifndef _END_GAME_H_
#define _END_GAME_H_

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Initialize the end of the game
void initEndGame();

//! Display the end of the game
/*!
  \param a boolean
*/
void displayEndGame(bool win);
//! Set the score of the player
/*
  \paran the score
*/
void setScore(int score);
//! Handle when a key is press on the keyboard.
/*!
  \param key an unsigned character
*/
void keyboardEndGame(unsigned char key);

#endif