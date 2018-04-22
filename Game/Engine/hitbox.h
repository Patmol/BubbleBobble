#include <stdbool.h>
#include <stdlib.h>

#ifndef _HITBOX_H_
#define _HITBOX_H_

/**************************************************************************/
/************************* STRUCTURES DEFINITIONS *************************/
/**************************************************************************/
//! The structure for a position in a 2D space.
typedef struct position {
    float x;            /*!< The position on the horizontal axe. */
    float y;            /*!< The position on the vertical axe. */
} Position;

//! The structure for a hitbox.
typedef struct hitbox {
    float height;       /*!< The height of the hitbox. */
    float width;        /*!< The width of the hitbox. */
    Position *origin;   /*!< The orgion position of the hitbox. */
} Hitbox;

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Check if two hitbox hit each others
/*!
  \param hitbox1 is a hitbox structure
  \param hitbox2 is a hitbox structure
*/
bool isHit(Hitbox *hitbox1, Hitbox *hitbox2);

#endif