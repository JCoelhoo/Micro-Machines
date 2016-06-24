#pragma once
#ifndef __STATICOBJECT_H_INCLUDED__   // if x.h hasn't been included yet...
#define __STATICOBJECT_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "GameObject.h"

class StaticObject : public GameObject {
public:
	StaticObject() : GameObject() {};

	StaticObject(Vector3 pos);

	~StaticObject();

	virtual void draw() = 0;

};

#endif