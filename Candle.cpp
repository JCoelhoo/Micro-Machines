#include <iostream>
#include <string>
#include "Candle.h"
using namespace std;

Candle::Candle()
{
	collisionMax = Vector3(LENGTH / 2, WIDTH / 2, HEIGHT / 2);
	collisionMin = collisionMax*(-1);
	init();
}

Candle::Candle(Vector3 pos) : Obstacle(pos)
{
	collisionMax = Vector3(LENGTH / 2, WIDTH / 2, HEIGHT / 2);
	collisionMin = collisionMax*(-1);
	init();
}

void Candle::setLight(LightSource* l) {
	_light = l;
}
LightSource* Candle::getLight() {
	return _light;
}
Candle::~Candle()
{
}
void Candle::draw() {
	
	Candle_material->draw();
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(_position.getX(), _position.getY(), _position.getZ());
	glTranslatef(0, 0, HEIGHT / 2);
	glPushMatrix();
	glScalef(LENGTH, WIDTH, HEIGHT);
	glutSolidCube(1.0);
	glPopMatrix();

	wick_material->draw();
	glColor3f(1, 0.7, 0);
	glTranslatef(0, 0, HEIGHT / 2+0.1);
	glScalef(0.2, 0.2, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();
	

	_light->setPosition(Vector3(_position.getX(), _position.getY(), _position.getZ() +  2*HEIGHT));
	_light->draw();

}

void Candle::collide(Car* player) {
	_velocity = player->_direction*player->v / 2;
	player->setAcceleration(0);
	player->v = 0;
}
void Candle::init() {
	GLfloat emission[4] = { 3.0f, 3.0f, 3.0f, 1.0f };

	wick_material = new Material(Vector3(0.2, 0.1, 0), Vector3(1, 0.6, 0), Vector3(0, 0, 0), Vector3(1, 0.6, 0), 18);
	Candle_material = new Material(Vector3(0.1, 0.1, 0.1), Vector3(1, 0.9, 0.9), Vector3(0, 0, 0), 18);
}
void Candle::candleEnable() {
	glEnable(getLight()->getNum());
	wick_material->setMaterialEmissive(Vector3(1, 0.6, 0));
}
void Candle::candleDisable() {
	glDisable(getLight()->getNum());
	wick_material->setMaterialEmissive(Vector3(0, 0, 0));
}
