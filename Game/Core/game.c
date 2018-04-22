#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "glut.h"
#include "game.h"
#include "../Engine/character.h"
#include "../Engine/weapon.h"

#define BLOC_WIDTH 25                   //! The width of a bloc of the wall
#define BLOC_HEIGHT 22                  //! The height of a bloc of the wall
#define TOP_SPACE 50                    //! The space at the top of the screen
#define BULLET_WIDTH 38                 //! The width of an image of a bullet
#define BULLET_HEIGHT 32                //! The height of an image of a bullet
#define BULLET_SPEED 20                 //! The default speed of a bullet
#define SHOT_LIMIT 30                   //! The time between every shot
#define SHOT_REMOVE_SAFE_ZONE 200       //! A pixel value outside the screen where we can safely remove the bullet from the list
#define ENNEMIES_NUMBER 2               //! The numbers of ennemies
#define ENNEMY_HIT 20                   //! The life remove when an ennmy touch a player
#define ENNEMY_HIT_TEMP 30              //! The timer between two hit of an ennemy

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
//! Make the ennemies catch the player
void ennemiesCatch();

/**************************************************************************/
/******************************* VARIABLES ********************************/
/**************************************************************************/
//! The state of the keyboard key
bool keyStates[256]; 
//! Show Bubble
bool showBubble = true;
//! The shot timer
int shotTimer = 0;
//! The ennemy timer
int ennemyTimer = 0;
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
    // We use a random number for the speed of the ennemies
    srand(time(NULL));
    // The name of the level
    char blocLevelName[100];
    // We generate the name of the bloc of the level (name like bloc-level-{levelNumber})
    sprintf(blocLevelName, "bloc-level-%d", level);
    
    bloc = getTexture(blocLevelName);

    // We generate the Bubble character with his texture and his weapon
    bubble = initializeCharacter("bubble", 10, 15, 0.0f, 0.0f, 126.0f, 133.0f);
    addCharacterTexture(bubble, "bubble-left", "left");
    addCharacterTexture(bubble, "bubble-right", "right");
    setBullet(bubble, "bubble-bullet", BULLET_HEIGHT, BULLET_WIDTH, BULLET_SPEED, 100);

    // We load the level
    loadLevel(level);
    // We initialize the ennemies
    ennemiesInit();
}
//! Display the game screen.
void displayGame() {
    // We clear the OpenGL bugger
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // we enable the 2D texture use to display texture in the game
    glEnable(GL_TEXTURE_2D);

    // Display the bullets
    bulletsDisplay();

    // Display character (bubble and ennemies)
    if (showBubble || ennemyTimer == 0) {
        characterDisplayManagement(bubble);
    }
    if (ennemyTimer != 0) {
        showBubble = !showBubble;
    }

    ennemiesDisplay();
    
    // We check the action of bubble (depending on the key press on the keyboard)
    bubbleAction();
    // We move the character
    moveCharacter(bubble, levelStructure);
    // We move the bullets
    bulletsMovement();
    // We check if some ennemies has been hit
    ennemiesHits();

    // Display the bloc of the level
    levelDisplay();

    // We disable the 2D texture
    glDisable(GL_TEXTURE_2D);
    
    // We swap the OpenGL buffer
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
    // ennemies try to catch Bubble
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
        ennemy->ennemy = initializeCharacter("ennemi", 
            15 + (rand() % 15), 
            15 + (rand() % 15), 
            (i * ((WINDOW_WIDTH * 2) / ENNEMIES_NUMBER)), 
            (WINDOW_WIDTH * 2) + 50,  126.0f, 133.0f);
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
    int numberOfEnnemiesLeft = 0;
    Ennemies *displayEnnemy = ennemies;

    while (displayEnnemy != NULL) {
        if (displayEnnemy->ennemy->life > 0) {
            characterDisplayManagement(displayEnnemy->ennemy);
            numberOfEnnemiesLeft++;
        }
        displayEnnemy = displayEnnemy->next;
    }

    if (numberOfEnnemiesLeft == 0) {
        changeGameStatus(END_GAME_WIN);
    }
}
//! Check if a bullet hit an ennemy
void ennemiesHits() {
    Bullets *checkBullet = bullets;
    Bullets *prevBullet = NULL;
    Ennemies *checkEnnemy = ennemies;

    while (checkBullet != NULL) {
        while (checkEnnemy != NULL) {
            if (checkBullet != NULL &&
                isHit(checkBullet->bullet->hitbox, checkEnnemy->ennemy->hitbox)) {
                // If we have a hit, we need to remove the bullet for the bullets list
                //  and change the life of the ennemy

                // We change the life of the ennemy
                if (checkEnnemy->ennemy->life >= 0) {
                    checkEnnemy->ennemy->life -= checkBullet->bullet->dammage;

                    // We remove the bullet if the life of the catch ennemy is greater than zero
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
                } 
            }
            
            checkEnnemy = checkEnnemy->next;
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
        // We only move the ennmy if his life is greater than zero
        if (moveEnnemy->ennemy->life > 0) {
            // Depending on the Bubble position, we change the direction of the ennemy
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

            if (isHit(moveEnnemy->ennemy->hitbox, bubble->hitbox) && ennemyTimer == 0) {
                    bubble->life -= ENNEMY_HIT;
                    ennemyTimer++;

                    if (bubble->life < 0) {
                        changeGameStatus(END_GAME_LOSE);
                    }
                }
        }

        if (ennemyTimer > 0 && ennemyTimer < ENNEMY_HIT_TEMP) {
            ennemyTimer++;
        } else {
            ennemyTimer = 0;
        }

        moveEnnemy = moveEnnemy->next;
    }
}