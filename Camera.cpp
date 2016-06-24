#include <iostream>
#include <string>
#include "Camera.h"
using namespace std;

Camera::Camera()
{
	_up = Vector3();
	_at = Vector3();
	this->setPosition(Vector3());
	_near = 0;
	_far = 1;

}

Camera::Camera(Vector3 eye, Vector3 at, Vector3 up, double near, double far) {
	_up = up;
	_at = at;
	this->setPosition(eye);
	_near = near;
	_far = far;
}

Camera::Camera(double near, double far)
{
	_up = Vector3();
	_at = Vector3();
	this->setPosition(Vector3());
	_near = near;
	_far = far;
}

Camera::~Camera()
{
}

void Camera::update()
{
}


void Camera::computeVisualizationMatrix()
{
	//gluLookAt(-30, -30, 30, 0, 0, 0, 0, 0, 1);
	gluLookAt(_position.getX(), _position.getY(), _position.getZ(), _at.getX(), _at.getY(), _at.getZ(), _up.getX(), _up.getY(), _up.getZ());
}
	
void Camera::setAt(Vector3 at) {
	_at = at;
}
	


