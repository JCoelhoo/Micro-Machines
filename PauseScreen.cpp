#include <iostream>
#include <string>
#include "PauseScreen.h"
#include "PauseScreen.h"
using namespace std;

PauseScreen::PauseScreen()
{
	init();

}

PauseScreen::PauseScreen(Vector3 pos) : StaticObject(pos)
{
	init();
}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::init() {
	pauseScreen_material = new Material(Vector3(), Vector3(1, 1, 1), Vector3(0, 0, 0), 62);
	pauseScreen_texture = new Texture("pause_screen.bmp");

}

void PauseScreen::move(Vector3 direction) {
	_position = _position + direction;
}

void PauseScreen::draw() {
	double i, j;
	glEnable(GL_TEXTURE_2D);

	pauseScreen_texture->draw();
	pauseScreen_material->draw();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(_position.getX(), _position.getY(), _position.getZ());

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0.4);
	glVertex3f(0, 0, 5);
	glTexCoord2d(0, 1.0);
	glVertex3f(0, 20, 5);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(30, 20, 5);
	glTexCoord2d(1.0, 0.4);
	glVertex3f(30, 0, 5);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


