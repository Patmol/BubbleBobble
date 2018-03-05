#ifndef _GLUT_H_
#define _GLUT_H_

#define TIMER 10

enum gameState { GAME, HELP, HOME, LOGO, SCORE  };

void init(void);
void display(void);
void reshape(int w, int h);
void timer(int value);
void keyboard(unsigned char key, int x, int y);

#endif