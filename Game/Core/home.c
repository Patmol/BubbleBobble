#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <string.h>

#include "home.h"
#include "../Engine/texture.h"

#define LOGO_Y_TRANSLATION 0.03

Texture* logo = NULL;
float logoYPosition = 2.5f;

void initHome(Texture *textures) {
    Texture *currentTexture = textures;

    do {
        if(strcmp("logo", currentTexture->name) == 0) {
            logo = currentTexture;
        }
        currentTexture = currentTexture->next;
    } while (currentTexture != NULL && logo == NULL);
}

void displayHome() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, logo->textureId);

    glTranslatef(0.0, logoYPosition, -3.5);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -0.6f, 0.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -0.6f, 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 0.6f, 0.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 0.6f, 0.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}

void timerHome() {
    if (logoYPosition > 0.4f) {
        logoYPosition -= LOGO_Y_TRANSLATION;
    }
}