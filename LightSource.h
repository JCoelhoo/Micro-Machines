#pragma once
#ifndef __LIGHTSOURCE_H_INCLUDED__   // if x.h hasn't been included yet...
#define __LIGHTSOURCE_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "Vector3.h"
#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "GameObject.h"

class LightSource : public GameObject {
private:
	double _ambient;
	double _diffuse;
	double _specular;
	double _cutoff=180;
	double _exponent=0;
	//double _exponent;
	float constant = 0;
	float linear = 0.1;
	float quadratic = 0.1;
	GLenum _num;
	bool _state;
	GLfloat light_ambient[4] = { 0.5f, 0.5f,0.5f,1.0f };
	GLfloat light_diffuse[4] = { 1.0f, 0.7f,0.7f,1.0f };
	GLfloat light_specular[4] = { 1.0f, 1.0f,1.0f,1.0f };
	GLfloat _direction[3] = { 0,0,1.0f};
	GLfloat _w;

public:
	
	LightSource();

	LightSource(GLenum light);

	LightSource(Vector3 pos, GLenum light);

	~LightSource();

	void init();

	bool getState();

	bool setState(bool state);

	void pointLight();

	void directionalLight();

	GLenum getNum();

	void setPosition(Vector3 pos);

	void setExponent(double exponent);

	void setCutoff(double cutoff);

	void setDirection(Vector3 direction);

	void setAmbient(Vector3 ambient);

	void setDiffuse(Vector3 diffuse);

	void setSpecular(Vector3 specular);

	void setAttenuation(float a, float b, float c);

	void draw();


};

#endif