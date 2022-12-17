#include "Copper.h"

OBJ* Copper::_Obj = nullptr;
Copper::Copper()
{
	name = "Copper";
	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Resource/", "Copper.obj");
	}
	obj = _Obj;

	Render::objectRender->AddObject(this);
}

Copper::~Copper()
{

}