#pragma once
#ifndef __GAMEMANAGER_H_INCLUDED__   // if x.h hasn't been included yet...
#define __GAMEMANAGER_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "GameObject.h"
#include "Camera.h"
#include "LightSource.h"
#include <vector>
#define TABLE_XMIN -25.
#define TABLE_XMAX 25.
#define TABLE_YMIN -16.
#define TABLE_YMAX 16.
#define PROXIMITY -3.
#define INITIAL_LIVES 3

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class GameManager {
	private:
		Camera* _cameras;
		LightSource _light_sources;
		int _lifeNumber=5;
		
	public:
		GameManager();

		~GameManager();

		void keyPressed(unsigned char key, int x, int y);

		void keyBoardDown(int key, int x, int y);
			
		void keyBoardUp(int key, int x, int y);

		void pointLight(const float x, const float y, const float z, const float amb, const float diff, const float spec);

		void onTimer(int argument);

		void idle();

		void update(int value);

		void init();

		void getNumLifes();
		void setNumLifes();
	
		
};

#endif