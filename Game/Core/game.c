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

#define LEVEL_WIDTH 32
#define LEVEL_HEIGHT 25
#define BLOC_WIDTH 25
#define BLOC_HEIGH 22
#define TOP_SPACE 50

// The texture of the bloc
Texture *bloc = NULL;
// The texture of Bubble
Texture *bubble = NULL;
// An array contening the structure of the level
int levelStructure[LEVEL_WIDTH][LEVEL_HEIGHT];

// Initialiaze the data for the game screen
void initGame(int level) {
    char blocLevelName[100];
    sprintf(blocLevelName, "bloc-level-%d", level);

    bloc = getTexture(blocLevelName);
    bubble = getTexture("bubble");
    loadLevel(level);
}
// Display the game screen
void displayGame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    // Display the bloc of the level
    // We load the texture of the bloc
    glBindTexture(GL_TEXTURE_2D, bloc->textureId);
    for (int i = 0; i < LEVEL_WIDTH; i++) {
        for (int j = 0; j < LEVEL_HEIGHT; j++) {
            // We use the PushMatrix and PopMatrix to always start from the center of the window for our coordonates
            if (levelStructure[i][j] != 0) {
                glPushMatrix();
                // We move to the position where we want to display our bloc
                glTranslatef(
                    -((((WINDOW_WIDTH - 25.0) - (BLOC_WIDTH * 2) * i) / 146.0)), 
                    ((((WINDOW_HEIGH - 19.0) - (BLOC_HEIGH * 2) * j) - TOP_SPACE) / 146.0), 
                    -10.0f);
                glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex3f(-((1.0/292.0) * (BLOC_WIDTH * 2)), -((1.0/282.0) * 44), 0.0f);

                    glTexCoord2f(1.0f, 0.0f);
                    glVertex3f(((1.0/292.0) * (BLOC_WIDTH * 2)), -((1.0/282.0) * 44), 0.0f);

                    glTexCoord2f(1.0f, 1.0f);
                    glVertex3f(((1.0/292.0) * (BLOC_WIDTH * 2)), ((1.0/282.0) * 44), 0.0f);

                    glTexCoord2f(0.0f, 1.0f);
                    glVertex3f(-((1.0/292.0) * (BLOC_WIDTH * 2)), ((1.0/282.0) * 44), 0.0f);
                glEnd();
                glPopMatrix();
            }
        }
    }

    // We need to display the character of the player
    glBindTexture(GL_TEXTURE_2D, bubble->textureId);
    glPushMatrix();
    glTranslatef(0.0f, 0.15f, -4.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-((1.0/292.0) * (BLOC_WIDTH * 2)), -((1.0/282.0) * 44), 0.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(((1.0/292.0) * (BLOC_WIDTH * 2)), -((1.0/282.0) * 44), 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(((1.0/292.0) * (BLOC_WIDTH * 2)), ((1.0/282.0) * 44), 0.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-((1.0/292.0) * (BLOC_WIDTH * 2)), ((1.0/282.0) * 44), 0.0f);        
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}
// Timer function to handle update of the game screen
void timerGame() {
}
// Handle the keyboard input
void keyboardGame(unsigned char key) {
}

// Load a level (send in parameter) from a file
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