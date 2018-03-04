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

// We will load all the textures used by the application
//  sourcesPath: path to the file with the path to the textures
//  return: return the 
Textures* loadTextures(char* sourcesPath) {
    char *path = NULL, *name = NULL, *fullPath = NULL;
    FILE *file = NULL;

    Textures* textures = malloc(sizeof(Textures));
    Textures* previousTexture = NULL;
    Textures* currentTexture = NULL;
    Texture* newTexture = NULL;

    // Get the path of the application
    getcwd(fullPath, sizeof(fullPath));
    // Generate the full path of the source file
    strcat(fullPath, sourcesPath);
    
    // Open the file
    file = fopen(fullPath, "r");

    if (file == NULL) {
        // The file with the textures was not found, the application must exit.
        printf("The file %s cannot be found\n", sourcesPath);
        exit (EXIT_FAILURE);
    } else {
        // We have found the file with the texture
        // We will load all textures and generating a textureId to use it in GLUT
        fscanf(file, "%s %s", path, name);

        while(!feof(file)) {
            // We save the information of the textures in a texture structure
            newTexture = malloc(sizeof(Texture));
            newTexture->filename = path;
            newTexture->name = name;
            newTexture->textureId = loadTGATexture(path);

            if (previousTexture == NULL) {
                // If we create the first texture, we need to save this texture as the first item in textures
                textures->data = newTexture;
                textures->next = NULL;
                previousTexture = textures;
            } else {
                // Otherwise, we need to add a new texture to the list
                // Save the texture in a node of the textures
                currentTexture = malloc(sizeof(Textures));
                previousTexture->next = currentTexture;
                currentTexture->data = newTexture;
                currentTexture->next = NULL;
                previousTexture = currentTexture;
            }

            printf("%s %s", path, name);

            fscanf(file, "%s", path);
        }
    }

    fclose(file);

    return textures;
}