#pragma once
#ifndef __Table_H_INCLUDED__   // if x.h hasn't been included yet...
#define __Table_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "StaticObject.h"
#include "Material.h"
#include "Texture.h"
#define TABLE_XMIN -26.
#define TABLE_XMAX 26.
#define TABLE_YMIN -15.
#define TABLE_YMAX 15.
#define BLOCK_SIZE .25
#define REPEAT 52.
#define STARTY 0.36
#define STARTX 0.
#define MAX_SIZE 60.


class Table : public StaticObject {
private:
	Material *table_material;
	Texture *table_texture;

public:

	Table();

	Table(Vector3 pos);

	~Table();

	void init();

	void move(Vector3 direction);

	void draw();

};

#endif