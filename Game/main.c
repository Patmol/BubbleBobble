#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "Core/glut.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bubble Bobble");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutTimerFunc(TIMER, timer, 0);
    glutTimerFunc(LONG_TIMER, longTimer, 0);
    glutTimerFunc(SCORE_TIMER, longerTimer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialInput);
    glutMainLoop();

    return 0;
}