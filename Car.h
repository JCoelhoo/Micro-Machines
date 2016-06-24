#pragma once
#ifndef __CAR_H_INCLUDED__   // if x.h hasn't been included yet...
#define __CAR_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "DynamicObject.h"
#include "Wheel.h"
#include "Material.h"
#include "LightSource.h"

#define PI 3.14159265
#define CARHEIGHT 2./SMALLNESS
#define CARLENGTH 5./SMALLNESS
#define CARWIDTH 15./SMALLNESS
#define UPCARWIDTH 7./SMALLNESS
#define PILARB 7./SMALLNESS
#define FRONTWINDOW 3.5/SMALLNESS
#define FRONTWINDOWPOS 3.5/SMALLNESS
#define BACKWINDOW 1./SMALLNESS
#define BACKWINDOWPOS 14./SMALLNESS
#define WHEELGAP 10.5/SMALLNESS
#define WHEELGAP1 1./SMALLNESS
#define SMALLNESS 20.


class Car : public DynamicObject { 
private:
	Wheel wheel1;
	Wheel wheel2;
	Wheel wheel3;
	Wheel wheel4;
	Vector3 _acceleration;
	Material *car_material, *glass, *headlight, *day_light;
	double _accelarationConst = 0.0000005;
	double _velocityCap = 7;
	double turningSpeedX, turningSpeedY;
	double turningSpeed = PI/2;
	double _turningRadius = 2;
	double _steerFriction = .2; //0->no friction at high speeds; 1->max friction
	double _initialPower = 0;
	double _power = 5;
	double steering = 0;
	bool headlights = false;
	LightSource* _leftHeadlight;
	LightSource* _rightHeadlight;

public:
	Vector3 _direction;
	double a, v;


public:
	Car();

	Car(Vector3 pos);

	void init();

	~Car();

	void setMaterial(Material * mat);

	void Car::update(double delta_t);

	void processCollision(GameObject * obj);

	void collide(Car* car) {};

	void draw();

	void setAcceleration(double num);

	void gas();

	void reverse();

	void Car::steerLeft();

	void Car::steerRight();
	void stopSteering();
	void enableHeadlights();
	void disableHeadlights();
	bool tableEnd(double xmin, double xmax, double ymin, double ymax);
	void drawPrism();
	void drawCurvedCube();
	void drawUnitCube();
};

#endif