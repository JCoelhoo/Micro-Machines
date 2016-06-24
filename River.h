#pragma once
#ifndef __RIVER_H_INCLUDED__   // if x.h hasn't been included yet...
#define __RIVER_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "Entity.h"

class River: public Entity {
	public:
		River();

		~River();

		void draw();

};

#endif