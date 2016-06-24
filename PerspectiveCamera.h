#pragma once
#ifndef __PRESPECTIVECAMERA_H_INCLUDED__   // if x.h hasn't been included yet...
#define __PRESPECTIVECAMERA_H_INCLUDED__   //   #define this so the compiler knows it has been included

#include "Camera.h"
#define PI 3.1415

class PerspectiveCamera : public Camera {

public:
	double _fovy;
	double _aspect;
public: 
	PerspectiveCamera(double fovy, double aspect, double zNear, double zFar);

	PerspectiveCamera(Vector3 eye, Vector3 at, Vector3 up, double fovy, double aspect, double zNear, double zFar);

	~PerspectiveCamera();

	void update();

	void computeProjectionMatrix();

	void reshape(double w, double h);

};

#endif