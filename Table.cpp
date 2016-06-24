#include <iostream>
#include <string>
#include "Table.h"
#include "Texture.h"
using namespace std;

Table::Table()
{
	init();

}

Table::Table(Vector3 pos) : StaticObject(pos)
{
	init();
}

Table::~Table()
{
}

void Table::init() {
	table_material = new Material(Vector3(), Vector3(1, 1, 1), Vector3(0, 0, 0), 62);
	table_texture = new Texture();

}

void Table::move(Vector3 direction) {
	_position = _position + direction;
}

void Table::draw() {
	double i, j;
	glEnable(GL_TEXTURE_2D);
	
	table_texture->draw();
	table_material->draw();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(_position.getX(), _position.getY(), _position.getZ());

	for (i = TABLE_XMIN; i < TABLE_XMAX; i += BLOCK_SIZE) {
		for (j = TABLE_YMIN; j < TABLE_YMAX; j += BLOCK_SIZE) {
			glPushMatrix();
			glTranslatef(i, j, 0);
			glScalef(BLOCK_SIZE, BLOCK_SIZE, 1);
			glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			//glTexCoord2d(0.0f, 0.0f);
			glTexCoord2d(STARTX + (i - TABLE_XMIN)/REPEAT, STARTY + (j - TABLE_YMIN)/REPEAT);
			glVertex3f(-0.5, -0.5, 0);
			//glTexCoord2d(0.0f, 1.0f);
			glTexCoord2d(STARTX + (i -TABLE_XMIN) / REPEAT, STARTY + (j+BLOCK_SIZE - TABLE_YMIN)/ REPEAT);
			glVertex3f(-0.5, 0.5, 0);
			//glTexCoord2d(1.0f, 1.0f);
			glTexCoord2d(STARTX + (i+BLOCK_SIZE - TABLE_XMIN) /REPEAT, STARTY + (j+BLOCK_SIZE - TABLE_YMIN) / REPEAT);
			glVertex3f(0.5, 0.5, 0);
			//glTexCoord2d(1.0f, 0.0f);
			glTexCoord2d(STARTX + (i + BLOCK_SIZE - TABLE_XMIN) / REPEAT, STARTY + (j - TABLE_YMIN) / REPEAT);
			glVertex3f(0.5, -0.5, 0);
			glEnd();
			glPopMatrix();
		}
	}
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


