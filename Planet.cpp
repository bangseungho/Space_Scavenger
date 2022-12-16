#include "Planet.h"

Planet::Planet() : Mesh(this)
{
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
