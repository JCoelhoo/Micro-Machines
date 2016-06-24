#pragma once
#ifndef __Candle_H_INCLUDED__   // if x.h hasn't been included yet...
#define __Candle_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "Obstacle.h"
#include "Car.h"
#include "Material.h"
#include "LightSource.h"

#define LENGTH 2./3
#define WIDTH 2./3
#define HEIGHT 1.5


class Candle : public Obstacle {
private:
	Material *Candle_material;
	Material *wick_material;
	LightSource* _light = NULL;
public:
	Candle();

	Candle(Vector3 pos);

	void setLight(LightSource *l);

	LightSource* getLight();

	~Candle();

	void draw();
	void collide(Car * player);
	void init();
	void candleEnable();
	void candleDisable();
};

#endif