#include <iostream>
#include <string>
#include "Roadside.h"
using namespace std;

Roadside::Roadside() {
	double outeri[3] = { -23, -14, 0 };
	double inneri[3] = {-20, -11, 0 };
	double pos[3];

	pos[0] = outeri[0];
	pos[1] = outeri[1];
	pos[2] = outeri[2];


	den = 2;
	//outside line
	drawLine(pos, 0, 26,0, den);
	drawLine(pos, 2, 2, 0, den);
	drawLine(pos, 8, 0, 0, den);
	drawLine(pos, 4, -6, 0, den);
	drawLine(pos, 3, 0, 0, den);
	drawLine(pos, 6, 6, 0, den);
	drawLine(pos, 17, 0, 0, den);
	drawLine(pos, 2, -2, 0, den);
	drawLine(pos, 0, -6, 0, den);
	drawLine(pos, 4, -4, 0, den);
	drawLine(pos, 0, -4, 0, den);
	drawLine(pos, -4, -4, 0, den);
	drawLine(pos, 0, -6, 0, den);
	drawLine(pos, -2, -2, 0, den);
	drawLine(pos, -17, 0, 0, den);
	drawLine(pos, -7, 14, 0, den);
	drawLine(pos, -3, 0, 0, den);
	drawLine(pos, -3, -13.6, 0, den);
	drawLine(pos, outeri[0] - pos[0], outeri[1] - pos[1], outeri[2] - pos[2], den);


	//inside line
	pos[0] = inneri[0];
	pos[1] = inneri[1];
	pos[2] = inneri[2];

	drawLine(pos, 0, 22, 0, den);
	drawLine(pos, 5, 0, 0, den);
	drawLine(pos, 4, -6, 0, den);
	drawLine(pos, 6, 0, 0, den);
	drawLine(pos, 6, 6, 0, den);
	drawLine(pos, 15, 0, 0, den);
	drawLine(pos, 0, -5, 0, den);
	drawLine(pos, -4, -4, 0, den);
	drawLine(pos, 0, -4, 0, den);
	drawLine(pos, 4, -4, 0, den);
	drawLine(pos, 0, -5, 0, den);
	drawLine(pos, -14, 0, 0, den);
	drawLine(pos, -7, 14, 0, den);
	drawLine(pos, -7, 0, 0, den);
	drawLine(pos, -3, -13.5, 0, den);
	drawLine(pos, inneri[0] - pos[0], inneri[1] - pos[1], inneri[2] - pos[2], den);

};

Roadside::~Roadside() {
}

void Roadside::update(double delta_t) {
	for (Cheerio &cheerio : _cheerios) {
		cheerio.update(delta_t);
	}
}

void Roadside::drawLine(double start[3], double x, double y, double z, double den) {
	double a = start[0];
	double b = start[1];
	double c = start[2];
	double i;
	double t = sqrt(x*x+y*y+z*z);
	//such that (x,y,z) is a unit vector:
	x = x / t;
	y = y / t;
	z = z / t;
	
	for (i = 0; i < t; i+= 1/den) {
		Cheerio cheerio = Cheerio(Vector3(a+i*x, b+i*y, c+i*z));
		_cheerios.push_back(cheerio);
	}
	
	start[0] = a + i*x;
	start[1] = b + i*y;
	start[2] = c + i*z;

}

bool Roadside::hasCollided(GameObject* obj) {
	for (Cheerio &cheerio : _cheerios) {
		if (cheerio.hasCollided(obj)) return true;
	}
	return false;
}

void Roadside::draw() {
	glPushMatrix();
	for (Cheerio &cheerio : _cheerios) {
		cheerio.draw();
	}
	glPopMatrix();
}

