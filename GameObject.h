#pragma once
#ifndef __GAMEOBJECT_H_INCLUDED__   // if x.h hasn't been included yet...
#define __GAMEOBJECT_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "Entity.h"

class GameObject : public Entity {
public:
	Vector3 collisionMin = Vector3();
	Vector3 collisionMax = Vector3();
	Vector3 _velocity = Vector3();

	public:
		GameObject();
		GameObject(Vector3 position);

		bool hasCollided(GameObject* obj);
		
		//virtual void collide(GameObject* obj) = 0;

		void processColision(GameObject * obj);

		~GameObject();

		void drawCollision();


		virtual void draw();

		virtual void update(double delta_t);

};

#endif