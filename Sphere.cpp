#include "Sphere.h"

OBJ* Sphere::_Obj = nullptr;

Sphere::Sphere() : Mesh(this)
{
	name = "Shpere";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj((char*)"Sphere.obj");
	}

	obj = _Obj;

	Render::objectRender->AddObject(this);
}

Sphere::~Sphere()
{
}