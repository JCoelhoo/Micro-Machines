#include <iostream>
#include <string>
#include "Butter.h"
using namespace std;

Butter::Butter()
{
	collisionMax = Vector3(LENGTH / 2, WIDTH / 2, HEIGHT / 2);
	collisionMin = collisionMax*(-1);
	init();
}

Butter::Butter(Vector3 pos) : Obstacle(pos)
{
	collisionMax = Vector3(LENGTH / 2, WIDTH / 2, HEIGHT / 2);
	collisionMin = collisionMax*(-1);
	init();
}

Butter::~Butter()
{
}
void Butter::draw(){
	butter_material->draw();
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(_position.getX(), _position.getY(), _position.getZ());
	glTranslatef(0, 0, HEIGHT/2);
	glScalef(LENGTH, WIDTH, HEIGHT);  
	glutSolidCube(1.0);
	glPopMatrix();

}

void Butter::collide(Car* player) {
	_velocity = player->_direction*player->v / 2;
	player->setAcceleration(0);
	player->v = 0;
}
void Butter::init() {
	butter_material = new Material(Vector3(.1, .1, .1), Vector3(.5, .5, 0), Vector3(0, 0, 0), 18);
}



