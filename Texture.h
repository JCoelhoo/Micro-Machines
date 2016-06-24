#pragma once
#ifndef __TEXTURE_H_INCLUDED__   // if x.h hasn't been included yet...
#define __TEXTURE_H_INCLUDED__   //   #define this so the compiler knows it has been included
#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <fstream>
class Texture
{
private:
	GLuint texture;
	GLubyte my_texels[64][64][4];
	char filename[128];
	unsigned char* pixels;
	GLuint _width, _height;
public:
	Texture();
	Texture(const char * filename);
	~Texture();
	void init();
	void draw();
	unsigned char * readBMP(char * filename);
};

#endif
