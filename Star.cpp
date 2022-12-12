#include "Star.h"

Star::Star(string objName) : Mesh(this)
{
	name = objName.substr(0, objName.size() - 4);

	obj = new OBJ;
	obj->ReadObj("Obj/Star/", objName);

	lightTypeIndex = 1;

	//light.shape.SetActive(false);

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
