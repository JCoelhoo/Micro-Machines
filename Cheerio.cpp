#include <iostream>
#include <string>
#include "Cheerio.h"
using namespace std;




Cheerio::Cheerio(Vector3 pos) : StaticObject(pos) {
	collisionMax = Vector3(OUTER_RADIUS, OUTER_RADIUS, INNER_RADIUS);
	collisionMin = collisionMax*(-1);
	init();
}

Cheerio::~Cheerio() {
	
}

void Cheerio::draw() {
	cheerio_material->draw();
	glPushMatrix();
	glColor3f(0.925,0.925, 0.184);
	glTranslatef(_position.getX(), _position.getY(), _position.getZ());
	glTranslated(0, 0, OUTER_RADIUS); //put cheerio in z=0
	glutSolidTorus(INNER_RADIUS, OUTER_RADIUS, 10, 20);
	glPopMatrix();
}

void Cheerio::collide(Car* player) {
	_velocity = player->_direction*player->v / 2;
	player->setAcceleration(0);
	player->v = 0;
}

void Cheerio::init() {
	
	cheerio_material= new Material(Vector3(0.2, 0.2, 0), Vector3(0.5, 0.5, 0), Vector3(0.6, 0.6f, 0.5f), 30);
}