#pragma once
#ifndef __Cheerio_H_INCLUDED__   // if x.h hasn't been included yet...
#define __Cheerio_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "StaticObject.h"
#include "Car.h"
#include "Material.h"

#define SMALLNESS 2.5
#define INNER_RADIUS 0.1 / SMALLNESS
#define OUTER_RADIUS 0.2 / SMALLNESS


class Cheerio : public StaticObject {
private:
	double _x;
	double _y;
	double _z;
	Material *cheerio_material;
public:

	Cheerio::Cheerio(Vector3 pos);
		
	~Cheerio();

	void draw();

	void collide(Car * player);

	void init();
	
};

#endif