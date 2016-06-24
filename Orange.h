#pragma once
#ifndef __ORANGE_H_INCLUDED__   // if x.h hasn't been included yet...
#define __ORANGE_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "Obstacle.h"
#include "Car.h"
#include "Material.h"

#define RADIUS .75
// degrees/second
#define INCREASEW 60 //levelling increasing speed
#define INITIALW 60 //initial speed
//milliseconds
//respawn between 1s and 5s
#define MIN_RESPAWN 1000 
#define MAX_RESPAWN 5000
//level increases between 10s and 20s
#define MIN_LEVEL 1000
#define MAX_LEVEL 2000

#define RESPAWNING 0
#define LEVELLING 1

class Orange : public Obstacle{
private:
	double _w = INITIALW;
	double _degrees = 0;
	Material *orange_material;
	Material *caule_material;
public:
	bool disabled = false;

public:
	Orange();

	Orange(Vector3 pos);

	void init();

	void nextLevel();

	void respawn();

	void update(double delta_t);

	void collide(Car* car);
	
	~Orange();
	

	void draw();
	
};

#endif