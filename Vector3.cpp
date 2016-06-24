#include <iostream>
#include <string>
#include "Vector3.h"
using namespace std;

Vector3::Vector3()
	{
		_x = 0;
		_y = 0;
		_z = 0;
	}

Vector3::Vector3(double x, double y, double z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

Vector3::~Vector3()
	{
	}

double  Vector3::length() const
{

	return sqrt(_x*_x + _y*_y + _z*_z);
}

double  Vector3::getX() const
	{

		return _x;
	}

double  Vector3::getY() const
	{
		return _y;
	}

double Vector3::getZ()  const
	{
		return _z;
	}

Vector3 Vector3::operator=(const Vector3 & vec)
	{
		_x = vec.getX();
		_y = vec.getY();
		_z = vec.getZ();
		return *this;
	}


Vector3 Vector3::operator*(double num) const
	{
		return Vector3(_x*num,_y*num,_z*num);
	}

Vector3 Vector3::operator/(double num) const
{
	return Vector3(_x/num, _y/num, _z/num);
}


Vector3 Vector3::operator+(const Vector3 & vec)
	{
		return Vector3(_x+vec.getX(), _y+vec.getY(), _z+vec.getZ());
	}

Vector3 Vector3::operator-(const Vector3 & vec)
	{
		return Vector3(_x-vec.getX(), _y-vec.getY(), _z-vec.getZ());
	}


void Vector3::set(double x, double y, double z)
	{
		_x = x;
		_y = y;
		_z = z;
	}





