#include "Planet.h"

Planet::Planet(string objName) : Mesh(this)
{
	name = objName.substr(0,objName.size() - 4);

	obj = new OBJ;
	obj->ReadObj("Obj/Planet/", objName);

	Render::objectRender->AddObject(this);
}

Planet::~Planet()
{
}
