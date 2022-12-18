#pragma once
#include "Render.h"

class Particle : public Object, public Mesh
{
	static OBJ* _Obj;

public:
	Particle();
	~Particle();

public:
	void Enable();
	void Update();

private:
	vec3 velocity;
};
