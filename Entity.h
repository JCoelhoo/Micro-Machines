#pragma once
#ifndef __ENTITY_H_INCLUDED__   // if x.h hasn't been included yet...
#define __ENTITY_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "Vector3.h"
#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
class Entity {
	public:
		Vector3 _position;
	public: 
		Entity();

		~Entity();

		Vector3 getPosition();

		Vector3 * setPosition(double x, double y, double z);

		Vector3 * setPosition(const Vector3 &p);
};

#endif