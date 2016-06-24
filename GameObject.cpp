#include <iostream>
#include <string>
#include "GameObject.h"
using namespace std;

GameObject::GameObject()
{
	_position = Vector3(0, 0, 0);	

}

GameObject::GameObject(Vector3 pos)
{
	_position = pos;
	
}
void GameObject::draw() {
	
}

void GameObject::update(double delta_t) {
	delta_t = delta_t / 1000; //ms->s
	_position = _position + _velocity*delta_t;
	_velocity = _velocity * .9;
}

bool GameObject::hasCollided(GameObject* obj) {
	//check if collided
	return (obj->_position.getX() + obj->collisionMin.getX() < this->_position.getX() + this->collisionMax.getX()) &&
		(obj->_position.getX() + obj->collisionMax.getX() > this->_position.getX() + this->collisionMin.getX()) 
		&&
		(obj->_position.getY() + obj->collisionMin.getY() < this->_position.getY() + this->collisionMax.getY()) &&
			(obj->_position.getY() + obj->collisionMax.getY() > this->_position.getY() + this->collisionMin.getY());
}

GameObject::~GameObject()
{
}
void GameObject::drawCollision() {
	//colision box
	glBegin(GL_QUADS);
	glVertex3f(this->_position.getX() + this->collisionMin.getX(), this->_position.getY() + this->collisionMin.getY(), 0);
	glVertex3f(this->_position.getX() + this->collisionMin.getX(), this->_position.getY() + this->collisionMax.getY(), 0);
	glVertex3f(this->_position.getX() + this->collisionMax.getX(), this->_position.getY() + this->collisionMax.getY(), 0);
	glVertex3f(this->_position.getX() + this->collisionMax.getX(), this->_position.getY() + this->collisionMin.getY(), 0);

	glEnd();
}







