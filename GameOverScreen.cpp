#include <iostream>
#include <string>
#include "GameOverScreen.h"
#include "GameOverScreen.h"
using namespace std;

GameOverScreen::GameOverScreen()
{
	init();

}

GameOverScreen::GameOverScreen(Vector3 pos) : StaticObject(pos)
{
	init();
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::init() {
	gameOverScreen_material = new Material(Vector3(), Vector3(1, 1, 1), Vector3(0, 0, 0), 62);
	gameOverScreen_texture = new Texture("gameover_screen.bmp");

}

void GameOverScreen::move(Vector3 direction) {
	_position = _position + direction;
}

void GameOverScreen::draw() {
	double i, j;
	glEnable(GL_TEXTURE_2D);

	gameOverScreen_texture->draw();
	gameOverScreen_material->draw();
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


