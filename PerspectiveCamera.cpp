#include <iostream>
#include <string>
#include "PerspectiveCamera.h"
using namespace std;

PerspectiveCamera::PerspectiveCamera(double fovy, double aspect, double zNear, double zFar) : Camera(zNear, zFar)
{
	_fovy = fovy;
	_aspect = aspect;
}

PerspectiveCamera::PerspectiveCamera(Vector3 eye, Vector3 at, Vector3 up,double fovy, double aspect, double zNear, double zFar) : Camera(eye, at, up, zNear, zFar)
{
	_fovy = fovy;
	_aspect = aspect;
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::update()
{
}

void PerspectiveCamera::computeProjectionMatrix()
{
	gluPerspective(_fovy, _aspect, _near, _far);
}


void PerspectiveCamera::reshape(double w, double h) {
	//_aspect = w/h;
	//calculate new fovy
	double a = tan((_fovy*2*PI/360) / 2) * 2 * _far;
	double increase = _aspect / (w / h);
	_aspect = (w / h);
	_fovy = 2 * atan(a*increase / (2 *_far)) * 360 / (2 * PI);
}


