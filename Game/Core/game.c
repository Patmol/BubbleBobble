#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "glut.h"
#include "game.h"
#include "../Engine/character.h"
#include "../Engine/weapon.h"

#define BLOC_WIDTH 25
#define BLOC_HEIGHT 22
#define TOP_SPACE 50
#define BULLET_WIDTH 38
#define BULLET_HEIGHT 32
#define BULLET_SPEED 20
#define SHOT_LIMIT 30
#define SHOT_REMOVE_SAFE_ZONE 200
#define ENNEMIES_NUMBER 1

/**************************************************************************/
/************************** FUNCTIONS DEFINITIONS *************************/
/**************************************************************************/
//! Load a level from a file
/*!
  \param an integer
*/
void loadLevel(int);
//! Display a level
void levelDisplay();
//! Manage the way the character is display. The character must have a left and a right texture.
/*!
  \param character is a pointer to a character.
*/
void characterDisplayManagement(Character *character);
//! Display a character
/*!
  \param character is a pointer to a character.
  \param textureId is a texture identifiant.
*/
void characterDisplay(Character *character, GLuint textureId);
//! Display the bullets
void bulletsDisplay();
//! Handle the action of the bubble character
void bubbleAction();
//! Make all bullets move
void bulletsMovement();
//! Initialize the ennemies
void ennemiesInit();
//! Display the ennemies
void ennemiesDisplay();
//! Check if a bullet hit an ennemy
void ennemiesHits();
//! Make the ennemies move
void ennemiesCatch();

/**************************************************************************/
/******************************* VARIABLES ********************************/
/**************************************************************************/
//! The state of the keyboard key
bool keyStates[256]; 
//! The shot timer
int shotTimer = 0;
//! An array contening the structure of the level
int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT];
//! The texture of the bloc
Texture *bloc = NULL;
//! The character 'Bubble'
Character *bubble = NULL;
//! The first pointer to the list of bullets
Bullets *bullets = NULL;
//! The first pointer to the list of ennemies
Ennemies *ennemies = NULL;

/**************************************************************************/
/************************ FUNCTIONS IMPLEMENTATION ************************/
/**************************************************************************/
//! Initialiaze the data for the game screen.
/*!
  \param an integer for the level to initialize
*/
void initGame(int level) {
    srand(time(NULL));
    char blocLevelName[100];
    sprintf(blocLevelName, "bloc-level-%d", level);

    bloc = getTexture(blocLevelName);

    // We generate the Bubble character with his texture
    bubble = initializeCharacter("bubble", 10, 15, 0.0f, 0.0f, 126.0f, 133.0f);
    addCharacterTexture(bubble, "bubble-left", "left");
    addCharacterTexture(bubble, "bubble-right", "right");
    setBullet(bubble, "bubble-bullet", BULLET_HEIGHT, BULLET_WIDTH, BULLET_SPEED);

    loadLevel(level);
    ennemiesInit();
}
//! Display the game screen.
void displayGame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    // Display the bullets
    bulletsDisplay();

    // Display Bubble
    characterDisplayManagement(bubble);
    ennemiesDisplay();
    
    bubbleAction();
    moveCharacter(bubble, levelStructure);
    bulletsMovement();
    ennemiesHits();

    // Display the bloc of the level
    levelDisplay();

    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}
//! Timer function to handle update of the game screen.
void timerGame() {
    moveCharacter(bubble, levelStructure);
    bulletsMovement();

    Ennemies *moveEnnemy = ennemies;

    while (moveEnnemy != NULL) {
        moveCharacter(moveEnnemy->ennemy, levelStructure);

        moveEnnemy = moveEnnemy->next;
    }
}
//! Timer function to handle update of the game screen.
void longTimerGame() {
    ennemiesCatch();
}
//! Handle when a key is press on the keyboard.
/*!
  \param key an unsigned character
*/
void keyboardGame(unsigned char key) {
    keyStates[key] = true;
}
//! Handle when a key is release on the keyboard.
/*!
  \param key an unsigned character
*/
void keyboardUpGame(unsigned char key) {
    keyStates[key] = false;
}
//! Load a level from a file
/*!
  \param an integer
*/
void loadLevel(int level) {
    FILE *file = NULL;

    char levelFileName[100];
    sprintf(levelFileName, "data/level-%d.txt", level);

    file = fopen(levelFileName, "r");

    if (file == NULL) {
        // The file with the level structure was not found, the application must exit.
        printf("The file %s cannot be found\n", levelFileName);   
        exit (EXIT_FAILURE);
    } else {
        // We load of the number into our levelStructure array
        for (int i = 0; i < LEVEL_HEIGHT; i++) {
            for (int j = 0; j < LEVEL_WIDTH; j++) {
                fscanf(file, "%d ", &levelStructure[j][i]);
            }
        }
    }

    fclose(file);
}
//! Display a level
void levelDisplay() {
     // We load the texture of the bloc
    glBindTexture(GL_TEXTURE_2D, bloc->textureId);
    for (int i = 0; i < LEVEL_WIDTH; i++) {
        for (int j = 0; j < LEVEL_HEIGHT; j++) {
            // We use the PushMatrix and PopMatrix to always start from the center of the window for our coordonates
            if (levelStructure[i][j] != 0) {
                glPushMatrix();
                // We move to the position where we want to display our bloc
                glTranslatef(
                    -(((WINDOW_WIDTH - 25.0) - (BLOC_WIDTH * 2) * i) / 146.0), 
                    ((((WINDOW_HEIGH - 19.0) - (BLOC_HEIGHT * 2) * j) - TOP_SPACE) / 146.0), 
                    -10.0f);
                glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(-((1.0/292.0) * (BLOC_WIDTH * 2)), -((1.0/282.0) * (BLOC_HEIGHT * 2)), 0.0f);

                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(((1.0/292.0) * (BLOC_WIDTH * 2)), -((1.0/282.0) * (BLOC_HEIGHT * 2)), 0.0f);

                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(((1.0/292.0) * (BLOC_WIDTH * 2)), ((1.0/282.0) * (BLOC_HEIGHT * 2)), 0.0f);

                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(-((1.0/292.0) * (BLOC_WIDTH * 2)), ((1.0/282.0) * (BLOC_HEIGHT * 2)), 0.0f);
                glEnd();
                glPopMatrix();
            }
        }
    }
}
//! Manage the way the character is display. The character must have a left and a right texture.
/*!
  \param character is a pointer to a character.
*/
void characterDisplayManagement(Character *character) {
    //  Depending of the movement of character, we use a different texture
    switch (character->move) {
        case LEFT:
            characterDisplay(character, getCharacterTexture(character, "left"));
            break;
        case RIGHT:
            characterDisplay(character, getCharacterTexture(character, "right"));
            break;
        case NONE:
            switch (character->prevMove) {
                case LEFT:
                    characterDisplay(character, getCharacterTexture(character, "left"));
                    break;
                case RIGHT:
                    characterDisplay(character, getCharacterTexture(character, "right"));
                    break;
                case NONE:
                    break;
            }
            break;
    }
}
//! Display a character
/*!
  \param character is a pointer to a character.
  \param textureId is a texture identifiant.
*/
void characterDisplay(Character *character, GLuint textureId) {
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Transform x/y position in pixel of the character in OpenGL (0,0) center position
    float x = -(WINDOW_WIDTH - (character->hitbox->width / 2) - character->position->x - ((BLOC_WIDTH * 2)) * 2) / 146.0;
    float y = -(WINDOW_HEIGH - ((character->hitbox->height / 2) + 6) - character->position->y - (BLOC_HEIGHT * 2) - TOP_SPACE) / 146.0;
    
    glPushMatrix();

    // We move to the position where we want to display our bloc
    glTranslatef(x, y, -10.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-((1.0/292.0) * (character->hitbox->width)), -((1.0/282.0) * (character->hitbox->height)), 0.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(((1.0/292.0) * (character->hitbox->width)), -((1.0/282.0) * (character->hitbox->height)), 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(((1.0/292.0) * (character->hitbox->width)), ((1.0/282.0) * (character->hitbox->height)), 0.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-((1.0/292.0) * (character->hitbox->width)), ((1.0/282.0) * (character->hitbox->height)), 0.0f);
    glEnd();
    glPopMatrix();
}
//! Display the bullets
void bulletsDisplay() {
    Bullets *displayBullets = bullets;

    while (displayBullets != NULL) {
        glBindTexture(GL_TEXTURE_2D, displayBullets->bullet->textureId);

        // Transform x/y position in pixel of the character in OpenGL (0,0) center position
        float x = -(WINDOW_WIDTH - (displayBullets->bullet->hitbox->width / 2) - displayBullets->bullet->position->x - ((BLOC_WIDTH * 2)) * 2) / 146.0;
        float y = -(WINDOW_HEIGH - ((displayBullets->bullet->hitbox->height / 2) + 6) - displayBullets->bullet->position->y - (BLOC_HEIGHT * 2) - TOP_SPACE) / 146.0;
            
        glPushMatrix();

        // We move to the position where we want to display our bloc
        glTranslatef(x, y, -10.0f);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-((1.0/292.0) * (displayBullets->bullet->hitbox->width)), -((1.0/282.0) * (displayBullets->bullet->hitbox->height)), 0.0f);

            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(((1.0/292.0) * (displayBullets->bullet->hitbox->width)), -((1.0/282.0) * (displayBullets->bullet->hitbox->height)), 0.0f);

            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(((1.0/292.0) * (displayBullets->bullet->hitbox->width)), ((1.0/282.0) * (displayBullets->bullet->hitbox->height)), 0.0f);

            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-((1.0/292.0) * (displayBullets->bullet->hitbox->width)), ((1.0/282.0) * (displayBullets->bullet->hitbox->height)), 0.0f);
        glEnd();
        glPopMatrix();
            
        displayBullets = displayBullets->next;
    }
}
//! Move the bubble character
void bubbleAction() {
    if (keyStates['q'] && keyStates['d']) {
        bubble->move = NONE;
    } else if (keyStates['q']) {
        bubble->move = LEFT;
        bubble->prevMove = LEFT;
    } else if (keyStates['d']) {
        bubble->move = RIGHT;
        bubble->prevMove = RIGHT;
    } else if (!keyStates['q'] && !keyStates['d']) {
        bubble->move = NONE;
    }

    if (keyStates['z']) {
        jumpCharacter(bubble, levelStructure);
    }

    if (keyStates['e']) {
        if (shotTimer == 0) {
            shotTimer++;
            Bullet *bullet = shot(bubble);

            // There is no bullets yet shot
            if (bullets == NULL) {
                bullets = malloc(sizeof(Bullets));
                bullets->bullet = bullet;
                bullets->next = NULL;
            } else {
                // Otherwise, we add the bullet at the begin of the list of bullets shot
                Bullets *newBullets = malloc(sizeof(Bullets));
                newBullets->bullet = bullet;
                newBullets->next = bullets;
                bullets = newBullets;
            }
        }
    }
}
//! Make all bullets move
void bulletsMovement() {
    Bullets *displayBullets = bullets;
    Bullets *prevDisplayBullets = NULL;

    while (displayBullets != NULL) {
        moveBullet(displayBullets->bullet);

        // We need to check the position of the bullet, if this bullet is out of the screen,
        // we need to free the memory for it
        if (displayBullets->bullet->position->x < (0 - SHOT_REMOVE_SAFE_ZONE) || 
            displayBullets->bullet->position->x > (PLAY_WIDTH_SIZE + SHOT_REMOVE_SAFE_ZONE)) {
                if (prevDisplayBullets == NULL) {
                    bullets = displayBullets->next;
                    // Free the bullets object
                    free(displayBullets);
                    displayBullets = bullets;
                } else {
                    prevDisplayBullets->next = displayBullets->next;
                    // Free the bullets object
                    free(displayBullets);
                    displayBullets = prevDisplayBullets->next;
                }
            } else {
                prevDisplayBullets = displayBullets;
                displayBullets = displayBullets->next;
            }
    }

    if (shotTimer > 0 && shotTimer < SHOT_LIMIT) {
        shotTimer++;
    } else {
        shotTimer = 0;
    }
}
//! Initialize the ennemies
void ennemiesInit() {
    Ennemies *prevEnnemy = NULL;
    Ennemies *ennemy = NULL;

    for (int i = 0; i < ENNEMIES_NUMBER; i++) {
        ennemy = malloc(sizeof(Ennemies));
        ennemy->ennemy = initializeCharacter("ennemi", 15 + (rand() % 15), 15 + (rand() % 15), (i * ((WINDOW_WIDTH * 2) / ENNEMIES_NUMBER)), (WINDOW_WIDTH * 2) + 50,  126.0f, 133.0f);
        addCharacterTexture(ennemy->ennemy, "ennemi-1-left", "left");
        addCharacterTexture(ennemy->ennemy, "ennemi-1-right", "right");
        ennemy->next = NULL;

        if (ennemies == NULL) {
            ennemies = ennemy;
            prevEnnemy = ennemy;
        } else {
            prevEnnemy->next = ennemy;
            prevEnnemy = ennemy;
        }
    }
}
//! Display the ennemies
void ennemiesDisplay() {
    Ennemies *displayEnnemy = ennemies;

    while (displayEnnemy != NULL) {
        characterDisplayManagement(displayEnnemy->ennemy);
        displayEnnemy = displayEnnemy->next;
    }
}
//! Check if a bullet hit an ennemy
void ennemiesHits() {
    Bullets *checkBullet = bullets;
    Bullets *prevBullet = NULL;
    Ennemies *checkEnnemy = ennemies;
    Ennemies *prevEnnemy = NULL;

    while (checkBullet != NULL) {
        while (checkEnnemy != NULL) {
            if (checkBullet != NULL && checkEnnemy != NULL && 
                isHit(checkBullet->bullet->hitbox, checkEnnemy->ennemy->hitbox)) {
                // If we have a hit, we need to remove the bullet for the bullets list
                //  and the ennemy from the ennemies list
                // We remove the bullet
                if (prevBullet == NULL) {
                    // It's the first bullet of the list
                    bullets = checkBullet->next;
                    free(checkBullet);
                    checkBullet = bullets;
                } else {
                    prevBullet->next = checkBullet->next;
                    free(checkBullet);
                    checkBullet = prevBullet;
                }
                // We remove the ennemy
                if (prevEnnemy == NULL) {
                    // It's the first bullet of the list
                    ennemies = checkEnnemy->next;
                    free(checkEnnemy);
                    checkEnnemy = ennemies;
                } else {
                    prevEnnemy->next = checkEnnemy->next;
                    free(checkEnnemy);
                    checkEnnemy = prevEnnemy;
                }
            }

            if (checkEnnemy != NULL) {
                checkEnnemy = checkEnnemy->next;
            }
        }

        if (checkBullet != NULL) {
            checkBullet = checkBullet->next;
        }
    }
}
//! Make the ennemies move
void ennemiesCatch() {
    Ennemies *moveEnnemy = ennemies;

    while (moveEnnemy != NULL) {
        if (moveEnnemy->ennemy->position->y > bubble->position->y) {
            if (bubble->position->x < WINDOW_WIDTH / 2) {
                moveEnnemy->ennemy->move = LEFT;
            } else {
                moveEnnemy->ennemy->move = RIGHT;
            }
        } else {
            if (moveEnnemy->ennemy->position->x > bubble->position->x) {
                moveEnnemy->ennemy->move = LEFT;
            } else {
                moveEnnemy->ennemy->move = RIGHT;
            }

            if (moveEnnemy->ennemy->position->y < bubble->position->y) {
                jumpCharacter(moveEnnemy->ennemy, levelStructure);
            }
        }

        moveEnnemy = moveEnnemy->next;
    }
}