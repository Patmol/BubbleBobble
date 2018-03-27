#include "../Engine/texture.h"
#include "../Engine/character.h"
#include "../Engine/weapon.h"

#ifndef _HOME_H_
#define _HOME_H_

/**************************************************************************/
/************************* STRUCTURES DEFINITIONS *************************/
/**************************************************************************/
//! The structure for a list of bullets
typedef struct bullets {
    Bullet *bullet;         /*!< A bullet */
    struct bullets *next;          /*!< The next bullet in the list */
} Bullets;

typedef struct ennemies {
    Character *ennemy;
    struct ennemies *next;
} Ennemies;

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Initialiaze the data for the game screen.
/*!
  \param an integer argument.
*/
void initGame(int);
//! Display the game screen.
void displayGame();
//! Timer function to handle update of the game screen.
void timerGame();
//! Timer function to handle update of the game screen.
void longTimerGame();
//! Handle when a key is press on the keyboard.
/*!
  \param key an unsigned character
*/
void keyboardGame(unsigned char key);
//! Handle when a key is release on the keyboard.
/*!
  \param key an unsigned character
*/
void keyboardUpGame(unsigned char key);

#endif