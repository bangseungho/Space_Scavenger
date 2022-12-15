#include "Star.h"

Star::Star(string objName) : Mesh(this)
{
	name = objName.substr(0, objName.size() - 4);

	obj = new OBJ;
	obj->ReadObj("Obj/Star/", objName);

	lightTypeIndex = 1;

	// Transform
	transform.local->rotation.x = RandomFloat(-90, 90);

	Render::objectRender->AddObject(this);
}

Star::~Star()
{
}

void Star::Init()
{
	for (const auto& world : transform.world)
	{
		light.transform.world.push_back(world);
	}
	light.transform.world.push_back(transform.local);
}

void Star::Update()
{
	transform.local->rotation.y += FrameTime::oneFrame;
}