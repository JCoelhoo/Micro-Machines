#pragma once
#ifndef __VECTOR3_H_INCLUDED__   // if x.h hasn't been included yet...
#define __VECTOR3_H_INCLUDED__   //   #define this so the compiler knows it has been included



class Vector3 {

private:
	double _x;
	double _y;
	double _z;

public:

	Vector3();

	Vector3(double x, double y, double z);

	~Vector3();
	double  Vector3::length() const;

	double  getX() const;

	double  getY() const;

	double getZ() const;

	Vector3 operator=(const Vector3 & vec);

	Vector3 operator*(double num) const;

	Vector3 operator/(double num) const;

	Vector3 operator+(const Vector3 & vec);

	Vector3 operator-(const Vector3 & vec);

	void set(double x, double y, double z);

};



#endif