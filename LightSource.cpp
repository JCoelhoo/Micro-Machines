#include <iostream>
#include <string>
#include "LightSource.h"

using namespace std;

LightSource::LightSource()
{
	init();
}


LightSource::LightSource(Vector3 pos, GLenum light) : GameObject (pos)
{
	_num = light;
	init();
}

LightSource::LightSource(GLenum light){
	_num = light;
	init();
}

LightSource::~LightSource()
{
}

void LightSource::init() {
	_w = 1.0f;
	GLfloat light_position[4] = { _position.getX(), _position.getY(), _position.getZ(), _w };
	glLightfv(_num, GL_AMBIENT, light_ambient);
	glLightfv(_num, GL_DIFFUSE, light_diffuse);
	glLightfv(_num, GL_SPECULAR, light_specular);
	glLightfv(_num, GL_POSITION, light_position);


	glLightf(_num, GL_CONSTANT_ATTENUATION,constant);
	glLightf(_num, GL_LINEAR_ATTENUATION, linear);
	glLightf(_num, GL_QUADRATIC_ATTENUATION, quadratic);

	glLightf(_num, GL_SPOT_CUTOFF, _cutoff);
	glLightf(_num, GL_SPOT_EXPONENT, _exponent);
	glLightfv(_num, GL_SPOT_DIRECTION, _direction);

}

bool LightSource::getState()
{
	return false;
}

bool LightSource::setState(bool state)
{
	return false;
}
void LightSource::pointLight() {
	_w = 1.0f;
}

void LightSource::directionalLight() {
	_w = 0.0f; 
}

GLenum LightSource::getNum()
{
	return _num;
}

void LightSource::setPosition(Vector3 pos)
{
	_position = pos;
}

void LightSource::setExponent(double exponent)
{
	_exponent = exponent;
}
void LightSource::setCutoff(double cutoff)
{
	_cutoff = cutoff;
}
void LightSource::setDirection(Vector3 direction)
{
	_direction[0] = direction.getX();
	_direction[1] = direction.getY();
	_direction[2] = direction.getZ();
}

void LightSource::setAmbient(Vector3 ambient)
{
	light_ambient[0] = ambient.getX();
	light_ambient[1] = ambient.getY();
	light_ambient[2] = ambient.getZ();
}

void LightSource::setDiffuse(Vector3 diffuse)
{
	light_diffuse[0] = diffuse.getX();
	light_diffuse[1] = diffuse.getY();
	light_diffuse[2] = diffuse.getZ();
}

void LightSource::setSpecular(Vector3 specular)
{
	light_specular[0] = specular.getX();
	light_specular[1] = specular.getY();
	light_specular[2] = specular.getZ();
}

void LightSource::setAttenuation(float a, float b, float c) {
	constant = a;
	linear = b;
	quadratic = c;
}

void LightSource::draw()
{
	GLfloat light_position[4] = { _position.getX(), _position.getY(), _position.getZ(), _w };
	glLightfv(_num, GL_POSITION, light_position);
	glLightf(_num, GL_SPOT_CUTOFF, _cutoff);
	glLightf(_num, GL_SPOT_EXPONENT, _exponent);
	glLightfv(_num, GL_SPOT_DIRECTION, _direction);
}
