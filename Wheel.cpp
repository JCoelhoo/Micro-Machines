#include <iostream>
#include <string>
#include "Wheel.h"
using namespace std;

Wheel::Wheel()
{
	wheel_material = new Material(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0.2, 0.2, 0.2), 5);
}

Wheel::~Wheel()
{
}

void Wheel::draw()
{

	wheel_material->draw();
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0, THICKNESS/2, WHEELOUTERRADIUS); //put wheel in z=0
	glTranslatef(_position.getX(), _position.getY(), _position.getZ());
	glRotated(90, 1, 0, 0);
	glBegin(GL_TRIANGLES);

		//lado 1
		glNormal3f(0,0, -1);
		glVertex3f(0, 0, 0);
		glNormal3f(0.5, 0.866,0);
		glVertex3f(WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, 0);
		glNormal3f(-0.5, 0.866, 0);
		glVertex3f(-WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, 0);

		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, 0);
		glNormal3f(0.5, 0.866, 0);
		glVertex3f(WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, 0);
		glNormal3f(1, 0, 0);
		glVertex3f(WHEELOUTERRADIUS, 0, 0);

		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, 0);
		glNormal3f(1, 0, 0);
		glVertex3f(WHEELOUTERRADIUS, 0, 0);
		glNormal3f(0.5, -0.866, 0);
		glVertex3f(WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, 0);

		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, 0);
		glNormal3f(0.5, -0.866, 0);
		glVertex3f(WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, 0);
		glNormal3f(-0.5, -0.866, 0);
		glVertex3f(-WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, 0);

		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, 0);
		glNormal3f(-0.5, -0.866, 0);
		glVertex3f(-WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, 0);
		glNormal3f(-1, 0, 0);
		glVertex3f(-WHEELOUTERRADIUS, 0, 0);

		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, 0);
		glNormal3f(-1, 0, 0);
		glVertex3f(-WHEELOUTERRADIUS, 0, 0);
		glNormal3f(-0.5, 0.866, 0);
		glVertex3f(-WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, 0);


		//lado 2
		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, THICKNESS);
		glNormal3f(0.5, 0.866, 0);
		glVertex3f(WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, THICKNESS);
		glNormal3f(-0.5, 0.866, 0);
		glVertex3f(-WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, THICKNESS);
		
		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, THICKNESS);
		glNormal3f(0.5, 0.866, 0);
		glVertex3f(WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, THICKNESS);
		glNormal3f(1, 0, 0);
		glVertex3f(WHEELOUTERRADIUS, 0, THICKNESS);

		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, THICKNESS);
		glNormal3f(1, 0, 0);
		glVertex3f(WHEELOUTERRADIUS, 0, THICKNESS);
		glNormal3f(0.5, -0.866, 0);
		glVertex3f(WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, THICKNESS);

		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, THICKNESS);
		glNormal3f(0.5, -0.866, 0);
		glVertex3f(WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, THICKNESS);
		glNormal3f(-0.5, -0.866, 0);
		glVertex3f(-WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, THICKNESS);

		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, THICKNESS);
		glNormal3f(-0.5, -0.866, 0);
		glVertex3f(-WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, THICKNESS);
		glNormal3f(-1, 0, 0);
		glVertex3f(-WHEELOUTERRADIUS, 0, THICKNESS);

		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, THICKNESS);
		glNormal3f(-1, 0, 0);
		glVertex3f(-WHEELOUTERRADIUS, 0, THICKNESS);
		glNormal3f(-0.5, 0.866, 0);
		glVertex3f(-WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, THICKNESS);

	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.5, 0.866, 0);
	glVertex3f(WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, 0);
	glNormal3f(-0.5, 0.866, 0);
	glVertex3f(-WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, 0);
	glNormal3f(-0.5, 0.866, 0);
	glVertex3f(-WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, THICKNESS);
	glNormal3f(0.5, 0.866, 0);
	glVertex3f(WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, THICKNESS);

	glNormal3f(0.5, 0.866, 0);
	glVertex3f(WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, 0);
	glNormal3f(1, 0, -1);
	glVertex3f(WHEELOUTERRADIUS, 0, 0);
	glNormal3f(1, 0, -1);
	glVertex3f(WHEELOUTERRADIUS, 0, THICKNESS);
	glNormal3f(0.5, 0.866, 0);
	glVertex3f(WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, THICKNESS);


	glNormal3f(1, 0, 0);
	glVertex3f(WHEELOUTERRADIUS, 0, 0);
	glNormal3f(0.5, -0.866, 0);
	glVertex3f(WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, 0);
	glNormal3f(0.5, -0.866, 0);
	glVertex3f(WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, THICKNESS);
	glNormal3f(1, 0, 0);
	glVertex3f(WHEELOUTERRADIUS, 0, THICKNESS);


	glNormal3f(0.5, -0.866, 0);
	glVertex3f(WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, 0);
	glNormal3f(-0.5, -0.866, 0);
	glVertex3f(-WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, 0);
	glNormal3f(-0.5, -0.866, 0);
	glVertex3f(-WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, THICKNESS);
	glNormal3f(0.5, -0.866, 0);
	glVertex3f(WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, THICKNESS);


	glNormal3f(-0.5, -0.866, 0);
	glVertex3f(-WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, 0);
	glNormal3f(-1, 0, 0);
	glVertex3f(-WHEELOUTERRADIUS, 0, 0);
	glNormal3f(-1, 0, 0);
	glVertex3f(-WHEELOUTERRADIUS, 0, THICKNESS);
	glNormal3f(-0.5, -0.866, 0);
	glVertex3f(-WHEELOUTERRADIUS / 2, -WHEELOUTERRADIUS, THICKNESS);


	glNormal3f(-1, 0, 0);
	glVertex3f(-WHEELOUTERRADIUS, 0, 0);
	glNormal3f(-0.5, 0.866, 0);
	glVertex3f(-WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, 0);
	glNormal3f(-0.5, 0.866, 0);
	glVertex3f(-WHEELOUTERRADIUS / 2, WHEELOUTERRADIUS, THICKNESS);
	glNormal3f(-1, 0, 0);
	glVertex3f(-WHEELOUTERRADIUS, 0, THICKNESS);

	

	glEnd();

	glPopMatrix();

}
