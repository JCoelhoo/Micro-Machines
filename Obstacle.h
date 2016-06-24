#pragma once
#ifndef __OBSTACLE_H_INCLUDED__   // if x.h hasn't been included yet...
#define __OBSTACLE_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "DynamicObject.h"
#include "Car.h"

class Obstacle : public DynamicObject {
public:
	Obstacle();

	Obstacle(Vector3 p) : DynamicObject(p) {  };

	~Obstacle();

	void draw();

	virtual void collide(Car* car) {};
};

#endif