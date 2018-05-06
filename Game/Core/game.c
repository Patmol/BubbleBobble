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
#include "end_game.h"
#include "../Engine/character.h"
#include "../Engine/weapon.h"
#include "../Engine/item.h"

#define BLOC_WIDTH 25                   //! The width of a bloc of the wall
#define BLOC_HEIGHT 22                  //! The height of a bloc of the wall
#define NUMBER_WIDTH 12                 //! The width of a number
#define NUMBER_HEIGHT 18                //! The height of a number
#define HEART_WIDTH 25                  //! The width of a heart
#define HEART_HEIGHT 22                 //! The height of a heart
#define TOP_SPACE 50                    //! The space at the top of the screen
#define BULLET_WIDTH 38                 //! The width of an image of a bullet
#define BULLET_HEIGHT 32                //! The height of an image of a bullet
#define BULLET_SPEED 20                 //! The default speed of a bullet
#define SHOT_LIMIT 30                   //! The time between every shot
#define SHOT_REMOVE_SAFE_ZONE 200       //! A pixel value outside the screen where we can safely remove the bullet from the list
#define START_ENNEMIES_NUMBER 2         //! The numbers of ennemies
#define TOTAL_ENNEMIES_NUMBER 10        //! The numbers of ennemies
#define ENNEMY_HIT 20                   //! The life remove when an ennmy touch a player
#define ENNEMY_HIT_TEMP 30              //! The timer between two hit of an ennemy
#define START_SCORE 500                 //! The starting score
#define ENNMIE_HIT_SCORE 50             //! The score we lose when an ennemy hit the player
#define NUMBER_OF_KEY 256               //! The number of key
#define BUFFER_SIZE 400                 //! The size of the buffer for the keyboard

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
//! Handle the action of the bobble character
void bobbleAction();
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
//! Display the items
void itemsDisplay();
//! Pickup the items
void itemsPickup();
//! Display the score
void scoreDisplay();
//! Display the life of the player
void lifeDisplayBubble();
//! Display the life of the player
void lifeDisplayBobble();


/**************************************************************************/
/******************************* VARIABLES ********************************/
/**************************************************************************/
//! The state of the keyboard key
bool keyStates[BUFFER_SIZE]; 
//! Show Bubble
bool showBubble = true;
//! Show Bobble
bool showBobble = true;
//! If the data need to be clean
bool dataNeedToBeClean = false;
//! The shot timer
int shotTimer = 0;
//! The ennemy timer
int ennemyTimerBubble = 0;
//! The ennemy timer
int ennemyTimerBobble = 0;
//! Number of ennemies created
int numberOfEnnemiesCreated = START_ENNEMIES_NUMBER;
//! The score of the player
int playerScore = START_SCORE;
//! The number of ennemies left
int numberOfEnnemiesLeft = 0;
//! The number of items left
int numberOfItemsLeft = 0;
//! An array contening the structure of the level
int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT];
//! The texture of the bloc
Texture *bloc = NULL;
//! The texture for the numbers
Texture* numbers[10];
//! The texture for the heart
Texture* heart;
//! The texture for the half heart
Texture* halfHeart;
//! The texture for the numbers
Texture* numbers[10];
//! The character 'Bubble'
Character *bubble = NULL;
//! The character 'Bubble'
Character *bobble = NULL;
//! The first pointer to the list of bullets
Bullets *bullets = NULL;
//! The first pointer to the list of ennemies
Ennemies *ennemies = NULL;
//! The first pointer to the list of items
Items *items = NULL;

/**************************************************************************/
/************************ FUNCTIONS IMPLEMENTATION ************************/
/**************************************************************************/
//! Initialiaze the data for the game screen.
/*!
  \param an integer for the level to initialize
*/
void initGame(int level) {
    dataNeedToBeClean = true;
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
    setBullet(bubble, "green-bullet", BULLET_HEIGHT, BULLET_WIDTH, BULLET_SPEED, 100);

    // We generate the Bobble character with his texture and his weapon if we have 2 players
    bobble = initializeCharacter("bobble", 10, 15, 0.0f, 0.0f, 126.0f, 133.0f);
    addCharacterTexture(bobble, "bobble-left", "left");
    addCharacterTexture(bobble, "bobble-right", "right");
    setBullet(bobble, "blue-bullet", BULLET_HEIGHT, BULLET_WIDTH, BULLET_SPEED, 100);

    // Load numbers texture
    numbers[0] = getTexture("0");
    numbers[1] = getTexture("1");
    numbers[2] = getTexture("2");
    numbers[3] = getTexture("3");
    numbers[4] = getTexture("4");
    numbers[5] = getTexture("5");
    numbers[6] = getTexture("6");
    numbers[7] = getTexture("7");
    numbers[8] = getTexture("8");
    numbers[9] = getTexture("9");

    // Load the hearts texture
    heart = getTexture("heart");
    halfHeart = getTexture("half-heart");

    // We load the level
    loadLevel(level);
    // We initialize the ennemies
    ennemiesInit();
}
//! Set the number of player
void setNumberOfPlayer(int numberOfPlayer) { 
    if (numberOfPlayer == 1) {
        bobble = NULL;
    }
}
//! Display the game screen.
void displayGame() {
    // We clear the OpenGL bugger
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // we enable the 2D texture use to display texture in the game
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); //I've seen this on most tutorials
    glDisable(GL_DEPTH_TEST);

    // Display the level and the HUD
    levelDisplay();
    scoreDisplay();
    lifeDisplayBubble();

    if (bobble != NULL) {
        lifeDisplayBobble();
    }

    // Display the UI elements under the character
    bulletsDisplay();
    itemsDisplay();

    // Display character (bubble and ennemies)
    if ((showBubble || ennemyTimerBubble == 0) && bubble->life > 0) {
        characterDisplayManagement(bubble);
    }
    if (bobble != NULL && ((showBobble || ennemyTimerBobble == 0) && bobble->life > 0)) {
        characterDisplayManagement(bobble);
    }
    if (ennemyTimerBubble != 0) {
        showBubble = !showBubble;
    }
    if (ennemyTimerBobble != 0) {
        showBobble = !showBobble;
    }

    // Display the UI elements over the character
    ennemiesDisplay();
    
    // We check the action of bubble (depending on the key press on the keyboard)
    bubbleAction();
    // We move the characters
    moveCharacter(bubble, levelStructure);
    
    // We check the action of bobble if this one exist and we move it
    if (bobble != NULL) {
        bobbleAction();
        moveCharacter(bobble, levelStructure);
    }
    // We move the bullets
    bulletsMovement();
    // We check if some ennemies has been hit
    ennemiesHits();
    // We check if the player pick an item
    itemsPickup();

    // We disable the 2D texture
    glDisable(GL_TEXTURE_2D);
    
    // We swap the OpenGL buffer
    glutSwapBuffers();

    if (numberOfEnnemiesLeft == 0 && numberOfItemsLeft == 0 && numberOfEnnemiesCreated == TOTAL_ENNEMIES_NUMBER) {
        setScore(playerScore);
        playerScore = START_SCORE;
        changeGameStatus(END_GAME_WIN);
    }
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
//! Timer function to handle update of the game screen.
void scoreTimerGame() {
    playerScore--;
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
//! Handle the special keys
void specialInputGame(int key, int x, int y) {
    keyStates[NUMBER_OF_KEY + key] = true;
}
//! Handle the special keys
void specialInputUpGame(int key, int x, int y) {
    keyStates[NUMBER_OF_KEY + key] = false;
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
                    ((((WINDOW_HEIGHT - 19.0) - (BLOC_HEIGHT * 2) * j) - TOP_SPACE) / 146.0), 
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
    float y = -(WINDOW_HEIGHT - ((character->hitbox->height / 2) + 6) - character->position->y - (BLOC_HEIGHT * 2) - TOP_SPACE) / 146.0;
    
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
        float y = -(WINDOW_HEIGHT - ((displayBullets->bullet->hitbox->height / 2) + 6) - displayBullets->bullet->position->y - (BLOC_HEIGHT * 2) - TOP_SPACE) / 146.0;
            
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
//! Move the bobble character
void bobbleAction() {
    if (keyStates[NUMBER_OF_KEY + GLUT_KEY_LEFT] && keyStates[NUMBER_OF_KEY + GLUT_KEY_RIGHT]) {
        bobble->move = NONE;
    } else if (keyStates[NUMBER_OF_KEY + GLUT_KEY_LEFT]) {
        bobble->move = LEFT;
        bobble->prevMove = LEFT;
    } else if (keyStates[NUMBER_OF_KEY + GLUT_KEY_RIGHT]) {
        bobble->move = RIGHT;
        bobble->prevMove = RIGHT;
    } else if (!keyStates[NUMBER_OF_KEY + GLUT_KEY_LEFT] && !keyStates[NUMBER_OF_KEY + GLUT_KEY_RIGHT]) {
        bobble->move = NONE;
    }

    if (keyStates[NUMBER_OF_KEY + GLUT_KEY_UP]) {
        jumpCharacter(bobble, levelStructure);
    }

    if (keyStates[NUMBER_OF_KEY + GLUT_KEY_DOWN]) {
        if (shotTimer == 0) {
            shotTimer++;
            Bullet *bullet = shot(bobble);

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

    for (int i = 0; i < START_ENNEMIES_NUMBER; i++) {
        ennemy = malloc(sizeof(Ennemies));
        ennemy->ennemy = initializeCharacter("ennemi", 
            15 + (rand() % 15), 
            15 + (rand() % 15),
            (i * ((WINDOW_WIDTH * 2) / START_ENNEMIES_NUMBER)), 
            (WINDOW_WIDTH * 2) + 50,  126.0f, 133.0f);
        addCharacterTexture(ennemy->ennemy, "ennemi-1-left", "left");
        addCharacterTexture(ennemy->ennemy, "ennemi-1-right", "right");
        ennemy->next = NULL;

        if (ennemies == NULL) {
            ennemies = ennemy;
            prevEnnemy = ennemy;
        } else if (prevEnnemy != NULL) {
            prevEnnemy->next = ennemy;
            prevEnnemy = ennemy;
        }
    }
}
//! Display the ennemies
void ennemiesDisplay() {
    numberOfEnnemiesLeft = 0;
    Ennemies *displayEnnemy = ennemies;

    while (displayEnnemy != NULL) {
        if (displayEnnemy->ennemy->life > 0) {
            characterDisplayManagement(displayEnnemy->ennemy);
            numberOfEnnemiesLeft++;
        }
        displayEnnemy = displayEnnemy->next;
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
                if (checkEnnemy->ennemy->life > 0) {
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

                    // If the life of the ennemy is 0, we generate an item
                    if (checkEnnemy->ennemy->life == 0) {
                        Item* item = initializeItem("item-pepper", 100, 
                            checkEnnemy->ennemy->position->x,
                            checkEnnemy->ennemy->position->y,
                            80,
                            100);

                        // It's the first item we generate
                        if (items == NULL) {
                            items = malloc(sizeof(Items));
                            items->item = item;
                            items->next = NULL;
                        } else {
                            Items* newItems = malloc(sizeof(Items));
                            newItems->item = item;
                            newItems->next = items;
                            items = newItems;
                        }
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
//! Make the ennemies move to catch the player
void ennemiesCatch() {
    Ennemies *moveEnnemy = ennemies;
    int ennemyNumber = 0;
    Character* playerToCatch =NULL;

    while (moveEnnemy != NULL) {
        // We only move the ennmy if his life is greater than zero
        if (moveEnnemy->ennemy->life > 0) {
            // We chose the player to catch
            if (bobble == NULL) {
                playerToCatch = bubble;
            } else {
                if (bubble->life == 0 || (ennemyNumber % 2 == 0 && bobble->life != 0)) {
                    playerToCatch = bobble;
                } else {
                    playerToCatch = bubble;
                }
            }

            // Depending on the Bubble position, we change the direction of the ennemy
            if (moveEnnemy->ennemy->position->y > playerToCatch->position->y) {
                if (playerToCatch->position->x < WINDOW_WIDTH / 2) {
                    moveEnnemy->ennemy->move = LEFT;
                } else {
                    moveEnnemy->ennemy->move = RIGHT;
                }
            } else {
                if (moveEnnemy->ennemy->position->x > playerToCatch->position->x) {
                    moveEnnemy->ennemy->move = LEFT;
                } else {
                    moveEnnemy->ennemy->move = RIGHT;
                }

                if (moveEnnemy->ennemy->position->y < playerToCatch->position->y) {
                    jumpCharacter(moveEnnemy->ennemy, levelStructure);
                }
            }

            if (isHit(moveEnnemy->ennemy->hitbox, playerToCatch->hitbox)) {
                if (playerToCatch == bubble && ennemyTimerBubble == 0) {
                    playerToCatch->life -= ENNEMY_HIT;
                    playerScore -= ENNMIE_HIT_SCORE;
                    ennemyTimerBubble++;
                } else if (playerToCatch == bobble && ennemyTimerBobble == 0) {
                    playerToCatch->life -= ENNEMY_HIT;
                    playerScore -= ENNMIE_HIT_SCORE;
                    ennemyTimerBobble++;
                }
            }

            ennemyNumber++;
        }

        if (bobble != NULL) {
            if (bubble->life <= 0 && bobble->life <= 0) {
                changeGameStatus(END_GAME_LOSE);
            }
        } else {
            if (bubble->life <= 0) {
                changeGameStatus(END_GAME_LOSE);
            }
        }

        if (ennemyTimerBubble > 0 && ennemyTimerBubble < ENNEMY_HIT_TEMP) {
            ennemyTimerBubble++;
        } else {
            ennemyTimerBubble = 0;
        }

        if (ennemyTimerBobble > 0 && ennemyTimerBobble < ENNEMY_HIT_TEMP) {
            ennemyTimerBobble++;
        } else {
            ennemyTimerBobble = 0;
        }

        moveEnnemy = moveEnnemy->next;
    }
}
//! Display the item
void itemsDisplay() {
    numberOfItemsLeft = 0;
    Items *displayItem = items;

    while (displayItem != NULL) {
        if (displayItem->item->scoreValue != 0 && displayItem->item->lifetime > 0) {
            // At each display, we decrease the life of the item. With this the player need to pickup the
            //  item in a certain amount of time
            displayItem->item->lifetime--;

            glBindTexture(GL_TEXTURE_2D, displayItem->item->textureId);

            // Transform x/y position in pixel of the character in OpenGL (0,0) center position
            float x = -(WINDOW_WIDTH - (displayItem->item->hitbox->width / 2) - displayItem->item->position->x - ((BLOC_WIDTH * 2)) * 2) / 146.0;
            float y = -(WINDOW_HEIGHT - ((displayItem->item->hitbox->height / 2) + 6) - displayItem->item->position->y - (BLOC_HEIGHT * 2) - TOP_SPACE) / 146.0;
                
            glPushMatrix();

            // We move to the position where we want to display our bloc
            glTranslatef(x, y, -10.0f);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(-((1.0/292.0) * (displayItem->item->hitbox->width)), -((1.0/282.0) * (displayItem->item->hitbox->height)), 0.0f);

                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(((1.0/292.0) * (displayItem->item->hitbox->width)), -((1.0/282.0) * (displayItem->item->hitbox->height)), 0.0f);

                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(((1.0/292.0) * (displayItem->item->hitbox->width)), ((1.0/282.0) * (displayItem->item->hitbox->height)), 0.0f);

                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(-((1.0/292.0) * (displayItem->item->hitbox->width)), ((1.0/282.0) * (displayItem->item->hitbox->height)), 0.0f);
            glEnd();
            glPopMatrix();
            numberOfItemsLeft++;
        }
        
        displayItem = displayItem->next;
    }
}
//! Pickup the items
void itemsPickup() {
    Items *pickItem = items;

    while (pickItem != NULL) {
        if (pickItem->item->lifetime > 0) {
            // We check if Bubble pick the item
            if (isHit(pickItem->item->hitbox, bubble->hitbox)) {
                playerScore += pickItem->item->scoreValue;
                // We change the score of the item pick
                pickItem->item->scoreValue = 0;
            }
            // We check if Bobble pick the item
            if (bobble != NULL && isHit(pickItem->item->hitbox, bobble->hitbox)) {
                playerScore += pickItem->item->scoreValue;
                // We change the score of the item pick
                pickItem->item->scoreValue = 0;
            }
        }

        pickItem = pickItem->next;
    }
}
//! Display the score
void scoreDisplay() {
    int currentScore = playerScore;
    if (currentScore < 0) {
        currentScore = 0;
    }

    for (int i = 0; i < 10; i++) {
        glBindTexture(GL_TEXTURE_2D, numbers[currentScore % 10]->textureId);
        currentScore /= 10;

        glPushMatrix();
        // We move to the position where we want to display our bloc
        glTranslatef(
            -(((WINDOW_WIDTH - 25.0) -200 + (NUMBER_WIDTH * 2) * i) / 146.0), 
            (((WINDOW_HEIGHT + 10) - (NUMBER_HEIGHT * 2)) / 146.0), 
            -10.0f);
        
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-((1.0/292.0) * (NUMBER_WIDTH * 2)), -((1.0/282.0) * (NUMBER_HEIGHT * 2)), 0.0f);
    
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(((1.0/292.0) * (NUMBER_WIDTH * 2)), -((1.0/282.0) * (NUMBER_HEIGHT * 2)), 0.0f);

            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(((1.0/292.0) * (NUMBER_WIDTH * 2)), ((1.0/282.0) * (NUMBER_HEIGHT * 2)), 0.0f);

            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-((1.0/292.0) * (NUMBER_WIDTH * 2)), ((1.0/282.0) * (NUMBER_HEIGHT * 2)), 0.0f);
        glEnd();
        glPopMatrix();
    }
}
//! Display the life of the player
void lifeDisplayBubble() {
    int playerNumberOfHeart = bubble->life / 20;
    for (int i = 0; i < playerNumberOfHeart; i++) {
        glBindTexture(GL_TEXTURE_2D, heart->textureId); 

        glPushMatrix();
        // We move to the position where we want to display our bloc
        glTranslatef(
            -(((WINDOW_WIDTH - 25.0) - (HEART_WIDTH * 2) * i) / 146.0), 
            -(((WINDOW_HEIGHT + 20) - (HEART_HEIGHT * 2)) / 146.0), 
            -10.0f);
                
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-((1.0/292.0) * (HEART_WIDTH * 2)), -((1.0/282.0) * (HEART_HEIGHT * 2)), 0.0f);
            
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(((1.0/292.0) * (HEART_WIDTH * 2)), -((1.0/282.0) * (HEART_HEIGHT * 2)), 0.0f);

            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(((1.0/292.0) * (HEART_WIDTH * 2)), ((1.0/282.0) * (HEART_HEIGHT * 2)), 0.0f);

            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-((1.0/292.0) * (HEART_WIDTH * 2)), ((1.0/282.0) * (HEART_HEIGHT * 2)), 0.0f);
        glEnd();
        glPopMatrix();
    }
}
//! Display the life of the player
void lifeDisplayBobble() {
    int playerNumberOfHeart = bobble->life / 20;
    for (int i = 0; i < playerNumberOfHeart; i++) {
        glBindTexture(GL_TEXTURE_2D, heart->textureId); 

        glPushMatrix();
        // We move to the position where we want to display our bloc
        glTranslatef(
            (((WINDOW_WIDTH - 25.0) - (HEART_WIDTH * 2) * i) / 146.0), 
            -(((WINDOW_HEIGHT + 20) - (HEART_HEIGHT * 2)) / 146.0), 
            -10.0f);
                
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-((1.0/292.0) * (HEART_WIDTH * 2)), -((1.0/282.0) * (HEART_HEIGHT * 2)), 0.0f);
            
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(((1.0/292.0) * (HEART_WIDTH * 2)), -((1.0/282.0) * (HEART_HEIGHT * 2)), 0.0f);

            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(((1.0/292.0) * (HEART_WIDTH * 2)), ((1.0/282.0) * (HEART_HEIGHT * 2)), 0.0f);

            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-((1.0/292.0) * (HEART_WIDTH * 2)), ((1.0/282.0) * (HEART_HEIGHT * 2)), 0.0f);
        glEnd();
        glPopMatrix();
    }
}
//! Create more ennemies
void popEnnemiTimerGame() {
    if (numberOfEnnemiesCreated < TOTAL_ENNEMIES_NUMBER) {
        Ennemies* ennemy = malloc(sizeof(Ennemies));
        ennemy->ennemy = initializeCharacter("ennemi", 
            15 + (rand() % 15), 
            15 + (rand() % 15),
            (80 + (rand() % 80)), 
            (WINDOW_WIDTH * 2) + 50,  126.0f, 133.0f);
        addCharacterTexture(ennemy->ennemy, "ennemi-1-left", "left");
        addCharacterTexture(ennemy->ennemy, "ennemi-1-right", "right");
        ennemy->next = ennemies;
        ennemies = ennemy;
        numberOfEnnemiesCreated++;
    }
}
//! Clear the game information
void clearGameInformation() {
    bullets = NULL;
    ennemies = NULL;
    items = NULL;

    bubble = NULL;
    bobble = NULL;

    // We reset all the keyboard buffer value
    for (int i = 0; i < BUFFER_SIZE; i++) {
        keyStates[i] = false;
    }

    // We reset the number of ennemies created
    numberOfEnnemiesCreated = START_ENNEMIES_NUMBER;
}