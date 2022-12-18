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
	SetActive(false);

	transform.local->scale = vec3(RandomFloat(0.3, 1.0));
	color.SetColor({ 1.0, 0.5, 0.0, 1.0 });
	velocity = RandomFloat(40, 60);


	Render::objectRender->AddObject(this, "Particle");
}

Particle::~Particle()
{
}

void Particle::Update()
{
	distance += velocity * FrameTime::oneFrame;
}