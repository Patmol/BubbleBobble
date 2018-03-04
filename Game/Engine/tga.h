#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifndef _TGA_H_
#define _TGA_H_

void GetTextureInfo(const struct tga_header_t *header, struct gl_texture_t *texinfo);
void ReadTGA8bits(FILE *fp, const GLubyte *colormap, struct gl_texture_t *texinfo);
void ReadTGA16bits(FILE *fp, struct gl_texture_t *texinfo);
void ReadTGA24bits(FILE *fp, struct gl_texture_t *texinfo);
void ReadTGA32bits(FILE *fp, struct gl_texture_t *texinfo);
void ReadTGAgray8bits(FILE *fp, struct gl_texture_t *texinfo);
void ReadTGAgray16bits(FILE *fp, struct gl_texture_t *texinfo);
void ReadTGA8bitsRLE(FILE *fp, const GLubyte *colormap, struct gl_texture_t *texinfo);
void ReadTGA16bitsRLE(FILE *fp, struct gl_texture_t *texinfo);
void ReadTGA24bitsRLE(FILE *fp, struct gl_texture_t *texinfo);
void ReadTGA32bitsRLE(FILE *fp, struct gl_texture_t *texinfo); 
void ReadTGAgray8bitsRLE(FILE *fp, struct gl_texture_t *texinfo);
void ReadTGAgray16bitsRLE(FILE *fp, struct gl_texture_t *texinfo);
struct gl_texture_t * ReadTGAFile(const char *filename);
GLuint loadTGATexture(const char *filename);

#endif