#pragma once
#ifndef __PauseScreen_H_INCLUDED__   // if x.h hasn't been included yet...
#define __PauseScreen_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "StaticObject.h"
#include "Material.h"
#include "Texture.h"



class PauseScreen : public StaticObject {
private:
	Material *pauseScreen_material;
	Texture *pauseScreen_texture;

public:

	PauseScreen();

	PauseScreen(Vector3 pos);

	~PauseScreen();

	void init();

	void move(Vector3 direction);

	void draw();

};

#endif