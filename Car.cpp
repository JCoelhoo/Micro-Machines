#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include "Car.h"

using namespace std;

Car::Car()
{
	init();
}

Car::Car(Vector3 pos) : DynamicObject(pos) {
	init();
}

void Car::init() {
	_acceleration = Vector3(); // acceler3ation vector
	_direction = Vector3(1, 0, 0); // direction vector
	wheel1 = Wheel(Vector3( WHEELGAP1, (CARLENGTH / 2), 0));
	wheel2 = Wheel(Vector3( WHEELGAP1, (-CARLENGTH / 2), 0));
	wheel3 = Wheel(Vector3( WHEELGAP1 + WHEELGAP, (CARLENGTH / 2), 0));
	wheel4 = Wheel(Vector3( WHEELGAP1 + WHEELGAP, (-CARLENGTH / 2), 0));
	turningSpeedX = cos(turningSpeed);
	turningSpeedY = sin(turningSpeed);
	v = 0; // velocity scalar
	a = 0; // acceleration scalar

	car_material  = new Material(Vector3(0.25f, 0.f, 0.f), Vector3(1.0f, 0.1f, 0.1f), Vector3(0.2f, 0.1f, 0.f), 3);
	glass = new Material(Vector3(0, 0, 0.1f), Vector3(1.0f, 1.0f, 0.5f), Vector3(0, 0, 0), 0);
	day_light = new Material(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.3f, 0.2f, 0.2f), Vector3(1.0f, 1.0f, 1.0f), 18);
	headlight = new Material(Vector3(), Vector3(1.0f, 1.0f, 1.0f), Vector3(), Vector3(0.8f, 0.8f, 0.8f), 1);
	_leftHeadlight = new LightSource(GL_LIGHT0);
	_rightHeadlight = new LightSource(GL_LIGHT7);
	_rightHeadlight->setCutoff(50);
	_rightHeadlight->setDirection(Vector3(-2, 0, 0));
	_rightHeadlight->setAttenuation(5, 1, 2);
	_rightHeadlight->setExponent(20);

	_leftHeadlight->setCutoff(50);
	_leftHeadlight->setDirection(Vector3(-2, 0, 0));
	_leftHeadlight->setAttenuation(5, 1, 2);
	_leftHeadlight->setExponent(20);
	glEnable(GL_LIGHT7);
	glEnable(GL_LIGHT0);
}

Car::~Car()
{
}

void Car::setMaterial(Material* mat) {
	car_material = mat;
}

void Car::update(double delta_t) {
	delta_t = delta_t / 1000;
	if (a == 0 || a*v < 0) { // velocity decay when not accelerating
		v = v * 0.90;
	}
	if (a*v < 0) { //brakes
		v = v*0.8;
	}
	if (v < _initialPower*_power && v > -_initialPower*_power) {
		v = 0;
	}

	if (steering != 0) { // turning
		double x = _direction.getX();
		double y = _direction.getY();
		_acceleration = Vector3((turningSpeedX*x - turningSpeedY*y*steering), (turningSpeedX*y + turningSpeedY*x*steering), 0);
	}
	else { // if moving in a straight line
		_acceleration = _direction;
	}
	if (v != 0) { // calculates new direction vector
		_direction = (_direction*abs(v) + _acceleration*delta_t*(pow(abs(v), 2-_steerFriction))/_turningRadius); //get new direction
		_direction = _direction / _direction.length(); //normaliz
	}
	else if (a != 0) {
		v = _initialPower*a;

	}

	if (v < _velocityCap && v > -_velocityCap/4) // if velocity hasn't hit capping point, velocity increases
		v = v + a*delta_t;

	_position = _position + _direction*v*delta_t; // change position

	_velocity = _direction * v;

	/*_leftHeadlight->_position = _position;
	_rightHeadlight->_position = _position;*/

	//update collision box:
	float xA, xB, xC, xD;
	float yA, yB, yC, yD;
	float x = _direction.getX();
	float y = _direction.getY();
	float a = CARWIDTH/2;
	float b = CARLENGTH/2;
	xA = a*x + y*b;
	yA = x*b - a*y;
	xB = x*(-a) + y*b;
	yB = x*b - (-a)*y;
	xC = a*x + y*(-b);
	yC = x*(-b) - a*y;
	xD = (-a)*x + y*(-b);
	yD = x*(-b) - (-a)*y;

	collisionMin = Vector3(std::min({ xA, xB, xC, xD }), std::min({ yA, yB, yC, yD }), -1);
	collisionMax = Vector3(std::max({ xA, xB, xC, xD }), std::max({ yA, yB, yC, yD }), -1);

}

void Car::processCollision(GameObject* obj) {
	double X1 = INFINITY, X2 = INFINITY, Y1 = INFINITY, Y2 = INFINITY;
	double a = 1;
	double least;
	Vector3 _dir = _direction * (abs(v) / v); //see if direction is positive or negative


	if( (obj->_position.getX() + obj->collisionMin.getX() < this->_position.getX() + this->collisionMax.getX()) &&
		(obj->_position.getX() + obj->collisionMax.getX() > this->_position.getX() + this->collisionMax.getX())) {
		//if right collision
		
		X1 = this->_position.getX() + this->collisionMax.getX() -( obj->_position.getX() + obj->collisionMin.getX());
		// X1 -> width of collision
		X1 = X1 / _dir.getX();
		if (X1 < 0) X1 = INFINITY; 
	}
	

	if ((obj->_position.getX() + obj->collisionMin.getX() < this->_position.getX() + this->collisionMin.getX()) &&
		(obj->_position.getX() + obj->collisionMax.getX() > this->_position.getX() + this->collisionMin.getX())) {
		//if left collision
		X2 = this->_position.getX() + this->collisionMin.getX() - (obj->_position.getX() + obj->collisionMax.getX());
		// X2 -> width of collision
		X2 = X2 / _dir.getX();
		if (X2 < 0) X2 = INFINITY;
	}
	if ((obj->_position.getY() + obj->collisionMin.getY() < this->_position.getY() + this->collisionMax.getY()) &&
		(obj->_position.getY() + obj->collisionMax.getY() > this->_position.getY() + this->collisionMax.getY())) {
		//if front collision
		Y1 = this->_position.getY() + this->collisionMax.getY() - (obj->_position.getY() + obj->collisionMin.getY());
		// Y1-> width of collision
		Y1 = Y1 / _dir.getY();
		if (Y1 < 0) Y1 = INFINITY;
	}
	if ((obj->_position.getY() + obj->collisionMin.getY() < this->_position.getY() + this->collisionMin.getY()) &&
		(obj->_position.getY() + obj->collisionMax.getY() > this->_position.getY() + this->collisionMin.getY())) {
		//if back collision
		Y2 = this->_position.getY() + this->collisionMin.getY() - (obj->_position.getY() + obj->collisionMax.getY());
		// Y2-> width of collision
		Y2 = Y2 / _dir.getY();
		if (Y2 < 0) Y2 = INFINITY;
	}
	if ((least = std::min({ X1, X2, Y1, Y2 })) < INFINITY) {
		//go back!!!
		_position = _dir*(-least) + _position;
	}

}

void Car::draw()
{
	double x = _direction.getX();
	double y = _direction.getY();
	GLdouble m[16] = { x, y, 0, 0, -y, x, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }; //rotation matrix

	

	glPushMatrix();

		glTranslated(_position.getX(), _position.getY(), _position.getZ());
		glMultMatrixd(m); //rotate 
		glPushMatrix();
			//glRotatef(-90, 1, 0, 0); //ver de lado
			glRotatef(180, 0, 0, 1);

			//glTranslatef(-.3, 0, 0); //EIXO ROTACAO
			//--------RODAS----------------
			glPushMatrix();
				glTranslatef(-CARWIDTH / 2, 0, 0);
				wheel1.draw();
				wheel2.draw();
				wheel3.draw();
				wheel4.draw();
				
			glPopMatrix();

			car_material->draw();
			//-------CARRO----------------------
			glPushMatrix();
				glTranslatef(0, 0, CARHEIGHT / 2 + WHEELOUTERRADIUS);
				// --------PARTE DO MEIO--------------
				glPushMatrix();
					glColor3f(1, 0, 0);
					glScalef(CARWIDTH, CARLENGTH, CARHEIGHT);
					drawUnitCube();
				glPopMatrix();
				
				glPushMatrix();
					glTranslatef(-CARWIDTH/2, -CARLENGTH / 2, 0);
					glPushMatrix();
						glTranslatef(0, 0.04, 0);
						_leftHeadlight->draw();
						glRotatef(90, 0, 1, 0);
						GLfloat a[4] = { 1.0f, 0.0f, 1.0f };
						glMaterialfv(GL_FRONT, GL_EMISSION, a);
						day_light->draw();
						glutSolidTorus(0.005, 0.02, 10, 10);
						headlight->draw();
						glutSolidSphere(0.010, 10, 10);
					glPopMatrix();
					

					glTranslatef(0, CARLENGTH, 0);

					glPushMatrix();
						glTranslatef(0, -0.04, 0);
						_rightHeadlight->draw();
						glRotatef(90, 0, 1, 0);
						day_light->draw();
						glutSolidTorus(0.005, 0.02, 10, 10);
						headlight->draw();
						glutSolidSphere(0.010, 10, 10);
					glPopMatrix();
					
				glPopMatrix();
				car_material->draw();
				//----------PARTE DE CIMA -------------------
				glPushMatrix();
					glTranslatef(-CARWIDTH / 2, 0, CARHEIGHT);
					glass->draw();
					//-----VIDRO DA FRENTE------------
					glTranslatef(FRONTWINDOWPOS + FRONTWINDOW / 2, 0, 0);
					glPushMatrix();
						glColor3f(1, 0, 0);
						glRotatef(180, 0, 0, 1);
						glRotatef(90, 1, 0, 0);
						glScalef(FRONTWINDOW, CARHEIGHT, CARLENGTH);
						drawPrism();
					glPopMatrix();
					car_material->draw();
					//------JANELAS MEIO-------------
					glTranslatef(FRONTWINDOW / 2 + UPCARWIDTH / 2, 0, 0);
					glPushMatrix();
						glColor3f(1, 0, 0);
						glScalef(UPCARWIDTH, CARLENGTH, CARHEIGHT);
						drawUnitCube();
						//drawCurvedCube();
						//glutSolidCube(1.0);
						glPopMatrix();
					glass->draw();
					//-----VIDRO DE TRAS---------------
					glTranslatef(BACKWINDOW / 2 + UPCARWIDTH / 2, 0, 0);
					glPushMatrix();
						glColor3f(1, 0, 0);
						glRotatef(90, 1, 0, 0);
						glScalef(BACKWINDOW, CARHEIGHT, CARLENGTH);
						
						drawPrism();
					glPopMatrix();

				glPopMatrix();

			glPopMatrix();

		glPopMatrix();
	glPopMatrix();

	

}

void Car::setAcceleration(double acceleration) {
	a = acceleration;
}

void Car::gas() {
	if (a < 0)
		steering = -steering;
	a = _power;
}

void Car::reverse() {
	if (a > 0)
		steering = -steering;
	a = - _power;
}

void Car::steerLeft() {
	if (a >= 0)
		steering = 1;
	else
		steering = -1;

}

void Car::steerRight() {
	if (a>=0)
		steering = -1;
	else 
		steering = 1;
}

void Car::stopSteering() {
	steering = 0;
}

void Car::enableHeadlights() {
	headlights = true;
	headlight->setMaterialEmissive(Vector3(0.8, 0.8, 0.8));
	glEnable(GL_LIGHT7);
	glEnable(GL_LIGHT0);
}

void Car::disableHeadlights() {
	headlights = false;
	headlight->setMaterialEmissive(Vector3());
	glDisable(GL_LIGHT7);
	glDisable(GL_LIGHT0);
}

bool Car::tableEnd( double xmin, double xmax, double ymin, double ymax) {
	double X1 = INFINITY, X2 = INFINITY, Y1 = INFINITY, Y2 = INFINITY;
	double a = 1;
	double least;
	Vector3 _dir = _direction * (abs(v) / v);
	if ((xmin > (this->_position.getX() + this->collisionMin.getX()))) {
		X1 = xmin - (this->_position.getX() + this->collisionMin.getX());
		X1 = abs(X1 / _dir.getX());
		
	}
	if (xmax< (this->_position.getX() + this->collisionMax.getX())) {
		X2 = this->_position.getX() + this->collisionMax.getX() - xmax;

		X2 = abs(X2 / _dir.getX());
		
	}
	if (ymax < (this->_position.getY() + this->collisionMax.getY())) {
		Y1 = this->_position.getY() + this->collisionMax.getY() - ymax;
		Y1 = abs(Y1 / _dir.getY());
		
	}
	if (ymin > (this->_position.getY() + this->collisionMin.getY())) {
		Y2 = ymin - (this->_position.getY() + this->collisionMin.getY());
		Y2 = abs(Y2 / _dir.getY());
		
	}
	
	if ((least = std::min({ X1, X2, Y1, Y2 })) < INFINITY) {
		v = 0;
		a = 0;
		_position = _dir*(-least) + _position;
		return true;
	}
	else {
		return false;
	}

}

void Car::drawPrism() {
	double a = 1, b = 1, c = 1;
	glPushMatrix();
	glTranslatef(-a / 2, -b / 2, -c / 2); //center the prism at origin
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, -1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, b, 0);
	glVertex3d(a, 0, 0);

	glNormal3d(0, 0, 1);
	glVertex3d(0, 0, c);
	glVertex3d(0, b, c);
	glVertex3d(a, 0, c);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3d(0, -1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, c);
	glVertex3d(a, 0, c);
	glVertex3d(a, 0, 0);

	glNormal3d(0.70710678118f, 0.70710678118f, 0);
	glVertex3d(0, b, 0);
	glVertex3d(0, b, c);
	glVertex3d(a, 0, c);
	glVertex3d(a, 0, 0);

	glNormal3d(-1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, c);
	glVertex3d(0, b, c);
	glVertex3d(0, b, 0);
	glEnd();
	glPopMatrix();

}

void Car::drawUnitCube() {
	double block = 0.5;
	glBegin(GL_QUADS);
	for (double i = 0; i < 1; i += block) {
		for (double j = 0; j < 1; j += block) {
			//glColor3f(0, 1, 0);
			glNormal3f(0, 0, -1);
			//face baixo

			glVertex3f(-0.5+i, -0.5+j, -0.5);
			glVertex3f(-0.5+i, 0.5-j, -0.5);
			glVertex3f(0.5-i, 0.5-j, -0.5);
			glVertex3f(0.5-i, -0.5+j, -0.5);

			glNormal3f(0, 0, 1);
			//face cima

			glVertex3f(-0.5+i, -0.5+j, 0.5);
			glVertex3f(-0.5+i, 0.5-j, 0.5);
			glVertex3f(0.5-i, 0.5-j, 0.5);
			glVertex3f(0.5-i, -0.5+j, 0.5);
			
			
			glNormal3f(-1, 0, 0);
			//face esquerda
			glVertex3f(-0.5, -0.5+i, -0.5+j);
			glVertex3f(-0.5, 0.5-i, -0.5+j);
			glVertex3f(-0.5, 0.5-i, 0.5-j);
			glVertex3f(-0.5, -0.5+i, 0.5-j);
			//glColor3f(1.0f, 1.0f, 0);
			
			glNormal3f(1, 0, 0);
			//face direita
			glVertex3f(0.5, -0.5+i, -0.5+j);
			glVertex3f(0.5, 0.5-i, -0.5+j);
			glVertex3f(0.5, 0.5-i, 0.5-j);
			glVertex3f(0.5, -0.5+i, 0.5-j);
			//glColor3f(0, 0, 1);
			//face frente
			glNormal3f(0, 1, 0);
			glVertex3f(-0.5+i, 0.5, -0.5+j);
			glVertex3f(0.5-i, 0.5, -0.5+j);
			glVertex3f(0.5-i, 0.5, 0.5-j);
			glVertex3f(-0.5+i, 0.5, 0.5-j);
			//face tras
			//glColor3f(0, 1, 0);
			glNormal3f(0, -1, 0);
			glVertex3f(-0.5+i, -0.5, -0.5+j);
			glVertex3f(0.5-i, -0.5, -0.5+j);
			glVertex3f(0.5-i, -0.5, 0.5-j);
			glVertex3f(-0.5+i, -0.5, 0.5-j);
		}
	}



	glEnd();
}

