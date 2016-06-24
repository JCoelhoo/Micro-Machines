#pragma once
#ifndef __MATERIAL_H_INCLUDED__   // if x.h hasn't been included yet...
#define __MATERIAL_H_INCLUDED__   //   #define this so the compiler knows it has been included
#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Vector3.h"

class Material {
private:
	GLfloat mat_shininess[1] = { 10.0f };
	GLfloat mat_specular[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_emission[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_ambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
public:
	Material(Vector3 ambient, Vector3 diffuse, Vector3 specular, double shine);
	Material(Vector3 ambient, Vector3 diffuse, Vector3 specular, Vector3 emissive, double shine);
	void draw();

	void setMaterialEmissive(Vector3 emissive);

};

#endif