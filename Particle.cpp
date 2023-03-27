#include "Particle.h"

OBJ* Particle::_Obj = nullptr;

Particle::Particle() : Mesh(this)
{
	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Default/", "Cube.obj");
	}
	obj = _Obj;

	name = "Particle";

	Render::objectRender->AddObject(this, "Particle");
}

Particle::~Particle()
{
}

void Particle::Enable()
{
	transform.local->scale = vec3(RandomFloat(0.3, 1.0));
	velocity = vec3(RandomFloat(-1, 1), RandomFloat(-1, 1), RandomFloat(-1, 1)) * RandomFloat(20,40);
	color.SetColor({ 1.0, 0.5, 0.0, 1.0 });
}

void Particle::Update()
{
	transform.local->position += velocity * FrameTime::oneFrame;
	color.A -= 0.03f;
}