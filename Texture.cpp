#include <iostream>
#include <string>
#include "Texture.h"



Texture::Texture()
{
	strcpy(filename, "mesa.bmp");
	init();
}
Texture::Texture(const char* name)
{
	strcpy(filename, name);
	init();
}

Texture::~Texture()
{
}

void Texture::init() {
	pixels = readBMP(filename);
	glGenTextures(1, &texture);
	
}

void Texture::draw() {
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, my_texels);
	//unsigned char test[12] = { 255, 255, 255, 0, 0, 0,0,0,0, 0, 0, 255};
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, test);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	
}
unsigned char* Texture::readBMP(char* filename)
{
	int i, j=0;
	FILE* f;
	f = fopen(filename, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
											   // extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];
	int size;

	//3 bytes per pixel + word-alignment
	size = 4 * width*height;
	unsigned char* file = new unsigned char[size];
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	int actual_size = fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);
	printf("%d %d %d\n", actual_size, size, 3*width*height);
	printf("%d %d\n", width, height);
	//account for BMP word-alignment
	unsigned char* cdata;
	/*if (width*height % 2 != 0) {
		file[0] = data[0];
		file[1] = data[1];
		file[2] = data[2];
		file[3] = 255;
		j = 4;
		cdata = &data[4];
	}
	else {
		cdata = data;
	}*/
	for (i=0; i < actual_size; i++) {
		//if ((actual_size != size || (i % 8) < 6) && (i!=actual_size-1)){
		file[j++] = data[i];
		if (j % 4 == 3) {
			unsigned char temp = file[j-1];
			file[j-1] = file[j - 3];
			file[j - 3] = temp;
			file[j++] = 255;
		}
	}
	_width = width;
	_height = height;
	printf("%d %d", _width, _height);
	free(data);
	return file;
}