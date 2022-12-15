#include "Cube.h"

OBJ* Cube::_Obj = nullptr;

Cube::Cube() : Mesh(this)
{
	name = "Cube";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Default/", "Cube.obj");
	}
	obj = _Obj;
	MeshInit();


	collider.tag = "Cube";
	collider.SetBox_OBB(vec3(2));
	collider.object = this;

	Render::objectRender->AddObject(this, "Cube");
}

Cube::~Cube()
{
}