#pragma once
#ifndef __GameOverScreen_H_INCLUDED__   // if x.h hasn't been included yet...
#define __GameOverScreen_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "StaticObject.h"
#include "Material.h"
#include "Texture.h"



class GameOverScreen : public StaticObject {
private:
	Material *gameOverScreen_material;
	Texture *gameOverScreen_texture;

public:

	GameOverScreen();

	GameOverScreen(Vector3 pos);

	~GameOverScreen();

	void init();

	void move(Vector3 direction);

	void draw();

};

#endif