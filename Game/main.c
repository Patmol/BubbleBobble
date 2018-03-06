#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "Core/glut.h"

/*
 * Request double buffer display mode
 * Register mouse input callback functions
 */
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
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}