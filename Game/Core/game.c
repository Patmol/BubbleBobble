#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "game.h"

Texture *bloc = NULL;
int levelStructure[32][25];

void initGame(int level) {
    char blocLevelName[100];
    sprintf(blocLevelName, "bloc-level-%d", level);

    bloc = getTexture(blocLevelName);
    loadLevel(level);
}
void displayGame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    // Display the bloc
    glBindTexture(GL_TEXTURE_2D, bloc->textureId);
    glTranslatef(-((800.0 - 19.0) / 146.0), ((600.0 - 19.0) / 146.0), -10.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-((1.0/292.0) * 50), -((1.0/282.0) * 44), 0.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(((1.0/292.0) * 50), -((1.0/282.0) * 44), 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(((1.0/292.0) * 50), ((1.0/282.0) * 44), 0.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-((1.0/292.0) * 50), ((1.0/282.0) * 44), 0.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}
void timerGame() {
}
void keyboardGame(unsigned char key) {
}

void loadLevel(int level) {
    FILE *file = NULL;

    char levelFileName[100];
    sprintf(levelFileName, "datas/level-%d.txt", level);

    file = fopen(levelFileName, "r");

    if (file == NULL) {
        // The file with the level structure was not found, the application must exit.
        printf("The file %s cannot be found\n", levelFileName);   
        exit (EXIT_FAILURE);
    } else {
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 32; j++) {
                fscanf(file, "%d ", &levelStructure[j][i]);
            }
        }
    }

    fclose(file);
}