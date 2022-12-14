#include "Planet.h"

Planet::Planet(string objName) : Mesh(this)
{
	name = objName.substr(0,objName.size() - 4);

	obj = new OBJ;
	obj->ReadObj("Obj/Planet/", objName);

	// Tranform
	transform.local->rotation.x = RandomFloat(-60, 60);

	Render::objectRender->AddObject(this);
}

Planet::~Planet()
{
}

void Planet::Update()
{
	transform.local->rotation.y += FrameTime::oneFrame;
}
