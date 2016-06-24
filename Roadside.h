#pragma once
#ifndef __ROADSIDE_H_INCLUDED__   // if x.h hasn't been included yet...
#define __ROADSIDE_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "StaticObject.h"
#include "Cheerio.h"
#include <vector>


class Roadside : public StaticObject {
public:
	std::vector<Cheerio> _cheerios;
	double den;
public:
	Roadside();

	~Roadside();

	void update(double delta_t);
	
	void draw();

	void drawLine(double start[3], double x, double y, double z, double den);

	bool hasCollided(GameObject * obj);
	

};

#endif