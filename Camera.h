#pragma once
#ifndef __CAMERA_H_INCLUDED__   // if x.h hasn't been included yet...
#define __CAMERA_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "Entity.h"

class Camera : public Entity {
	public:
		double _near;
		double _far;
		Vector3 _up, _at, _eye;

		Camera();

		Camera(Vector3 up, Vector3 at, Vector3 eye, double near, double far);

		Camera(double near, double far);

		~Camera();

		virtual void update() = 0;

		virtual void computeProjectionMatrix() = 0;

		virtual void computeVisualizationMatrix();
		void setAt(Vector3 at);
		virtual void reshape(double w, double h) = 0;

};

#endif