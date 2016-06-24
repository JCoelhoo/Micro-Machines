#include <iostream>
#include <string>
#include "Orange.h"
#include <time.h>  

using namespace std;

Orange::Orange() : Obstacle() {
	init();
}

Orange::Orange(Vector3 pos) : Obstacle(pos) {
	init();
}

void Orange::init() {
	collisionMax = Vector3(RADIUS, RADIUS, RADIUS);
	collisionMin = collisionMax*(-1);
	this->respawn();

	/*RED_PLASTIC*/
	//ambient, diffuse, specular, shine
	orange_material = new Material(Vector3(0.25, 0.1, 0), Vector3(1, 0.4, 0), Vector3(0.1, 0.f, 0.f), 50);
	caule_material = new Material(Vector3(0, 0, 0), Vector3(0.349, 0.243, 0.102), Vector3(0.03, 0.02, 0.01), 5);

}

void Orange::nextLevel() {

	//increase speed
	_w += rand() % INCREASEW; 
	setSpeed(_w * 2 * PI*RADIUS / 360); //increase speed whit random value
}

void Orange::respawn() {
	int x = rand() % 6 + 20;
	int y = rand() % 16;
	if ((rand() % 2) == 0) x = x*(-1); 
	if ((rand() % 2) == 0) y = y*(-1);
	
	_position = Vector3(x, y, 0); //change orange position
	setSpeed(_w * 2 * PI*RADIUS / 360); //set orange speed
	setDirection(Vector3(((double)rand() / (RAND_MAX)) - 0.5, ((double)rand() / (RAND_MAX)) - 0.5, 0)); //set orange direction
	_degrees = 0;
	disabled = false; 
}


void Orange::update(double delta_t) {
	

	delta_t = delta_t / 1000; //ms -> s
	_degrees = _degrees + _w*delta_t; //calculate angle. angle = angle + w*t

	if (_degrees >= 360) 
		_degrees -= 360;
	
	_position = getSpeed() * delta_t + _position; 

}

void Orange::collide(Car* player) {
	printf("GAME OVER\n");
	player->setPosition(-18, -12, 0);
	player->setAcceleration(0);
	player->v = 0;
	player->_direction = Vector3(1, 0, 0);
}



void Orange::draw() {
	
	if (!disabled) {
		orange_material->draw();
		glPushMatrix();
		glColor3f(1, 0.278, 0.039);
		glTranslated(_position.getX(), _position.getY(), _position.getZ());
		glTranslated(0, 0, RADIUS); //put range in z=0
		glRotated(_degrees, - getSpeed().getY(), getSpeed().getX(), 0);
		glutSolidSphere(RADIUS, 25, 50);
		glColor3f(.1, 0.278, 0.039);
		
		//CAULE
		caule_material->draw();
		glTranslated(0, 0, RADIUS); 
		glutSolidCube(0.25);
		glPopMatrix();
		
	}

}