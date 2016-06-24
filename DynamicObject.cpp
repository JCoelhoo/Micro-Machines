#include <iostream>
#include <string>
#include "DynamicObject.h"
using namespace std;

DynamicObject::~DynamicObject()
{
}


void DynamicObject::setSpeed(const Vector3 &speed)
{
	v = speed.length();
	if (v!=0)
		_direction = speed / v;
}

void DynamicObject::setSpeed(double speed)
{
	v = speed;
}

void DynamicObject::setDirection(const Vector3 &direction)
{
	_direction = direction / direction.length();
}


void DynamicObject::setSpeed(double x, double y, double z)
{
	this->setSpeed(Vector3(x, y, z));
}

Vector3 DynamicObject::getSpeed()
{
	return _direction * v;
}




