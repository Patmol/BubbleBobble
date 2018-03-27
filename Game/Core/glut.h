#ifndef _GLUT_H_
#define _GLUT_H_

#define TIMER 10
#define LONG_TIMER 40
#define WINDOW_WIDTH 800
#define WINDOW_HEIGH 600

enum gameState { GAME, HELP, HOME, LOGO, SCORE  };

void init(void);
void display(void);
void reshape(int w, int h);
void timer(int value);
void longTimer(int value);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);

#endif