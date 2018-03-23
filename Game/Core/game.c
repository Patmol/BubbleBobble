#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "glut.h"
#include "game.h"
#include "../Engine/character.h"
#include "../Engine/weapon.h"

#define BLOC_WIDTH 25
#define BLOC_HEIGHT 22
#define TOP_SPACE 50

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

/**************************************************************************/
/******************************* VARIABLES ********************************/
/**************************************************************************/
bool keyStates[256]; 
//! The texture of the bloc
Texture *bloc = NULL;
//! The character 'Bubble'
Character *bubble = NULL;
//! An array contening the structure of the level
int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT];
//! The first pointer to the list of bullets
Bullets *bullets = NULL;

/**************************************************************************/
/************************ FUNCTIONS IMPLEMENTATION ************************/
/**************************************************************************/
//! Initialiaze the data for the game screen.
/*!
  \param an integer for the level to initialize
*/
void initGame(int level) {
    char blocLevelName[100];
    sprintf(blocLevelName, "bloc-level-%d", level);

    bloc = getTexture(blocLevelName);

    // We generate the Bubble character with his texture
    bubble = initializeCharacter("bubble", 0.0f, 0.0f, 126.0f, 133.0f);
    addCharacterTexture(bubble, "bubble-left", "left");
    addCharacterTexture(bubble, "bubble-right", "right");
    setBulletTexture(bubble, "bubble-bullet");

    loadLevel(level);
}
//! Display the game screen.
void displayGame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    // Display Bubble
    //  Depending of the movement of Bubble, we use a different texture
    switch (bubble->move) {
        case LEFT:
            characterDisplay(bubble, getCharacterTexture(bubble, "left"));
            break;
        case RIGHT:
            characterDisplay(bubble, getCharacterTexture(bubble, "right"));
            break;
        case NONE:
            switch (bubble->prevMove) {
                case LEFT:
                    characterDisplay(bubble, getCharacterTexture(bubble, "left"));
                    break;
                case RIGHT:
                    characterDisplay(bubble, getCharacterTexture(bubble, "right"));
                    break;
                case NONE:
                    break;
            }
            break;
    }
    
    bubbleAction();
    move(bubble, levelStructure);

    // Display the bloc of the level
    levelDisplay();
    bulletsDisplay();

    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}
//! Timer function to handle update of the game screen.
void timerGame() {
    move(bubble, levelStructure);
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
        jump(bubble, levelStructure);
    }

    if (keyStates['e']) {
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