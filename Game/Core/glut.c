#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "glut.h"
#include "home.h"
#include "game.h"
#include "../Engine/texture.h"

enum gameState state = LOGO;

// Initalize all data require for the game
void init(void) {
    glShadeModel (GL_SMOOTH);

    glEnable (GL_DEPTH_TEST);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // We need to load all textures of the application at the initialisation
    loadTextures("data/images.txt");
    // Initialise the logo data
    initLogo();
    // Initialise the data for the game
    initGame(1);
}

// Function call by GLUT to display the screen
void display(void) {
    switch (state) {
        case GAME:
            displayGame();
            break;
        case HELP:
            break;
        case HOME:
            displayHome();
            break;
        case LOGO:
            displayLogo();
            break;
        case SCORE:
            break;
    }
}
// Function call by GLUT every X secondes
void timer(int value) {
    switch (state) {
        case GAME:
            timerGame();
            break;
        case HELP:
            break;
        case HOME:
            timerHome();
            break;
        case LOGO:
            timerLogo();
            break;
        case SCORE:
            break;
        
    }
    glutPostRedisplay();
    glutTimerFunc(TIMER, timer, 0);
}
// Function call by GLUT when the window is resize
void reshape(int w, int h) {
    if (h == 0) {
        h = 1;
    }
    
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, w/(GLdouble)h, 0.1, 1000.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glutPostRedisplay();
}
// Function call by GLUT to handle the keyboard
void keyboard(unsigned char key, int x, int y) {
    /* Escape */
    if (key == 27) {
        exit(0);
    }

    switch (state) {
        case GAME:
            keyboardGame(key);
            break;
        case HELP:
            break;
        case HOME:
            // Carriage return
            if (key == 13) {
                state = GAME;
            }
            break;
        case LOGO:
            // Carriage return
            if (key == 13) {
                state = HOME;
            }
            break;
        case SCORE:
            break;
    }
}