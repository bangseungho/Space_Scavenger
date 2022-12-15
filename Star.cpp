#include "Star.h"

OBJ* Star::_Obj = nullptr;

Star::Star() : Mesh(this)
{
	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Star/", "Sun.obj");
	}
	obj = _Obj;
	MeshInit();

	name = "Sun";

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