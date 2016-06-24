#pragma once
#ifndef __ORTHOGONALCAMERA_H_INCLUDED__   // if x.h hasn't been included yet...
#define __ORTHOGONALCAMERA_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "Camera.h"

class OrthogonalCamera : public Camera {

	private:
		double _left;
		double _right;
		double _bottom;
		double _top;
		double _deltaX;
		double _deltaY;

		
	public: 
		OrthogonalCamera(double left, double right, double bottom, double top, double near, double far);

		~OrthogonalCamera();

		void update();

		void computeProjectionMatrix();

		void computeVisualizationMatrix();

		void reshape(double w, double h);
};

#endif