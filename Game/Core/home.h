#include "../Engine/texture.h"

#ifndef _HOME_H_
#define _HOME_H_

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Initialiaze the data for the logo screen
void initLogo();
//! Display the logo screen
void displayLogo();
//! Timer function to handle update of the logo screen
void timerLogo();
//! Initialiaze the data for the home screen
void initHome();
//! Display the home screen
void displayHome();
//! Timer function to handle update of the home screen
void timerHome();
//! Handle when a key is press on the keyboard.
/*!
  \param key an unsigned character
*/
void keyboardHome(unsigned char key);
//! Initialiaze the data for the controls screen
void initControls();
//! Display the controls screen
void displayControls();
//! Handle when a key is press on the keyboard.
/*!
  \param key an unsigned character
*/
void keyboardControls(unsigned char key);

#endif