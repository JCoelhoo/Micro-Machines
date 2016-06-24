#pragma once
#ifndef __DYNAMICOBJECT_H_INCLUDED__   // if x.h hasn't been included yet...

#define __DYNAMICOBJECT_H_INCLUDED__   //   #define this so the compiler knows it has been included

#include "GameObject.h"
#include "Vector3.h"

#define PI 3.1415

class DynamicObject : public GameObject{
	private:
	Vector3 _direction = Vector3(1,0,0);
	double v = 0;

	public:
		DynamicObject::DynamicObject() : GameObject() {};

		DynamicObject::DynamicObject(Vector3 pos) : GameObject(pos) {};

		DynamicObject::~DynamicObject();

		void DynamicObject::setSpeed(const Vector3 &speed);

		void setSpeed(double speed);

		void setDirection(const Vector3 & direction);

		void DynamicObject::setSpeed(double x, double y, double z);

		virtual void draw() = 0;

		virtual void update() {}

		Vector3 DynamicObject::getSpeed();
		
};
#endif