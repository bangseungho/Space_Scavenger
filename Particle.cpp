#include "Particle.h"

OBJ* Particle::_Obj = nullptr;

Particle::Particle()
{
	name = "Particle";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj((char*)"Sphere.obj");
	}
	obj = _Obj;

	transform.local->scale = vec3(10);

	Render::objectRender->AddObject(this, "Particle");
}

Particle::~Particle()
{
}


void Particle::Update()
{
	
}
