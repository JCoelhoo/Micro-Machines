#pragma once
#pragma once
#ifndef __WHEEL_H_INCLUDED__   // if x.h hasn't been included yet...
#define __WHEEL_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "DynamicObject.h"
#include "Material.h"

#define SMALLNESS 20
#define WHEELOUTERRADIUS 1.25/SMALLNESS
#define WHEELINNERRADIUS 0.5/SMALLNESS
#define THICKNESS WHEELOUTERRADIUS/2 




class Wheel : public DynamicObject {
private:
	Material *wheel_material;
public:
	Wheel();
	Wheel(Vector3 pos) : DynamicObject(pos) { wheel_material = new Material(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0.2, 0.2, 0.2), 5); };

	~Wheel();

	void draw();
};

#endif