#pragma once
#ifndef __BUTTER_H_INCLUDED__   // if x.h hasn't been included yet...
#define __BUTTER_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "Obstacle.h"
#include "Car.h"
#include "Material.h"

#define LENGTH 0.75
#define WIDTH 3.
#define HEIGHT 1.5


class Butter : public Obstacle {
private:
	Material *butter_material;
	public: 
		Butter();

		Butter(Vector3 pos);

		~Butter();

		void move(Vector3 direction);

		void draw();
		void collide(Car * player);
		void init();
};

#endif