#include <iostream>
#include <string>
#include "OrthogonalCamera.h"
using namespace std;
OrthogonalCamera::OrthogonalCamera(double left, double right, double bottom, double top, double near, double far) : Camera(near, far)
{
	_deltaX = 0;
	_deltaY = 0;

	_left = left;
	_right = right;
	_top = top;
	_bottom = bottom;
}

OrthogonalCamera::~OrthogonalCamera()
{
}

void OrthogonalCamera::update()
{
}

void OrthogonalCamera::computeProjectionMatrix()
{
	glOrtho(_left - _deltaX, _right + _deltaX, _bottom - _deltaY, _top + _deltaY, _near, _far);
}

void OrthogonalCamera::computeVisualizationMatrix()
{

}

void OrthogonalCamera::reshape(double w, double h) {
	double aspect = w / h;
	float ratio = (_right - _left) / (_top - _bottom);
	if (ratio < aspect) {
		_deltaX = ((_top - _bottom) * aspect - (_right - _left)) / 2;
		_deltaY = 0;
	}
	else {
		_deltaY = ((_right - _left) / aspect - (_top - _bottom)) / 2;
		_deltaX = 0;
	}
}

