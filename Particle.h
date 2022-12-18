#pragma once
#include "Render.h"

class Particle : public Object, public Mesh
{
	static OBJ* _Obj;

public:
	Particle();
	~Particle();

public:
	void Update();

public:
	int distancePitch;
	int distanceYaw;
	float velocity;
	float distance;
};
