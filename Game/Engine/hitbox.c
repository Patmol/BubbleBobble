#include <stdbool.h>
#include <stdlib.h>

#include "hitbox.h"

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Check if two hitbox hit each others
/*!
  \param hitbox1 is a hitbox structure
  \param hitbox2 is a hitbox structure
*/
bool isHit(Hitbox *hitbox1, Hitbox *hitbox2) {
    // We check if on the X axe, we have a hit
    if ((hitbox2->origin->x >= hitbox1->origin->x && hitbox2->origin->x <= hitbox1->origin->x + hitbox1->width) ||
       (hitbox2->origin->x + hitbox2->width >= hitbox1->origin->x && hitbox2->origin->x + hitbox2->width <= hitbox1->origin->x + hitbox1->width)) {
           // If we have a hit on the X axe, we check the Y axe
           if ((hitbox2->origin->y >= hitbox1->origin->y && hitbox2->origin->y <= hitbox1->origin->y + hitbox1->height) ||
              (hitbox2->origin->y + hitbox2->height >= hitbox1->origin->y && hitbox2->origin->y + hitbox2->height <= hitbox1->origin->y + hitbox1->height)) {
                  return true;
           }
       }

    // We check if on the X axe, we have a hit
    if ((hitbox1->origin->x >= hitbox2->origin->x && hitbox1->origin->x <= hitbox2->origin->x + hitbox2->width) ||
       (hitbox1->origin->x + hitbox1->width >= hitbox2->origin->x && hitbox1->origin->x + hitbox1->width <= hitbox2->origin->x + hitbox2->width)) {
           // If we have a hit on the X axe, we check the Y axe
           if ((hitbox1->origin->y >= hitbox2->origin->y && hitbox1->origin->y <= hitbox2->origin->y + hitbox2->height) ||
              (hitbox1->origin->y + hitbox1->height >= hitbox2->origin->y && hitbox1->origin->y + hitbox1->height <= hitbox2->origin->y + hitbox2->height)) {
                  return true;
           }
       }

    return false;
}   