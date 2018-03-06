#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "texture.h"
#include "tga.h"

// Contains the list of all texture used by the application
Texture* textures;

// Load all the textures used by the application
//  sourcesPath: path to the file with the path to the textures
void loadTextures(char* sourcesPath) {
    char path[100], 
         name[40];
    FILE *file = NULL;

    // The first texture of the list
    Texture *firstTexture = NULL;
    // The previous texture of the list (used to link the texture between them)
    Texture *previousTexture = NULL;
    // The new texture that we will add in the list
    Texture *newTexture = NULL;

    // Open the file
    file = fopen(sourcesPath, "r");

    if (file == NULL) {
        // The file with the textures was not found, the application must exit.
        printf("The file %s cannot be found\n", sourcesPath);   
        exit (EXIT_FAILURE);
    } else {
        // We have found the file with the texture
        // We will load all textures and generating a textureId to use it in GLUT
        do {
            fscanf(file, "%s %s", path, name);

            // We create a new texture
            newTexture = malloc(sizeof(Texture));
            // We copy the string found in the file in the texture object
            strcpy(newTexture->filename, path);
            strcpy(newTexture->name, name);
            newTexture->textureId = loadTGATexture(path);
            newTexture->next = NULL;

            // Depending of the state of the variable, we are at the first item of the list or not
            if (firstTexture == NULL) {
                firstTexture = newTexture;
                previousTexture = newTexture;
            } else {
                previousTexture->next = newTexture;
                previousTexture = newTexture;
            }
        } while(!feof(file));
    }

    fclose(file);

    textures = firstTexture;
}

// Get a specific texture
//  name: the name of the texture to get
//  return: the texture structure
Texture* getTexture(char *name) {
    Texture *currentTexture = textures;
    Texture *texture = NULL;
    
    // Search through the list of texture, the one we need.
    do {
        if(strcmp(name, currentTexture->name) == 0) {
            texture = currentTexture;
        }
        currentTexture = currentTexture->next;
    } while (currentTexture != NULL && texture == NULL);

    return texture;
}