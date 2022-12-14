#pragma once
#include "Equipment.h"

class Particle : public Equipment
{
	static OBJ* _Obj;

public:
	Particle();
	~Particle();

public:
	void Update();
};
