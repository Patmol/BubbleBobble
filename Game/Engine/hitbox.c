#include <stdbool.h>
#include <stdlib.h>

#include "hitbox.h"

//! Check if two hitbox hit each others
/*!
  \param hitbox1 is a hitbox structure
  \param hitbox2 is a hitbox structure
*/
bool isHit(Position *position1, Hitbox *hitbox1, Position *position2, Hitbox *hitbox2) {
    // We check if on the X axe, we have a hit
    if ((position2->x >= position1->x && position2->x <= position1->x + hitbox1->width) ||
       (position2->x + hitbox2->width >= position1->x && position2->x + hitbox2->width <= position1->x + hitbox1->width)) {
           // If we have a hit on the X axe, we check the Y axe
           if ((position2->y >= position1->y && position2->y <= position1->y + hitbox1->height) ||
              (position2->y + hitbox2->height >= position1->y && position2->y + hitbox2->height <= position1->y + hitbox1->height)) {
                  return true;
           }
       }

    if ((position1->x >= position2->x && position1->x <= position2->x + hitbox2->width) ||
       (position1->x + hitbox1->width >= position2->x && position1->x + hitbox1->width <= position2->x + hitbox2->width)) {
           // If we have a hit on the X axe, we check the Y axe
           if ((position1->y >= position2->y && position1->y <= position2->y + hitbox2->height) ||
              (position1->y + hitbox1->height >= position2->y && position1->y + hitbox1->height <= position2->y + hitbox2->height)) {
                  return true;
           }
       }

       return false;
}   