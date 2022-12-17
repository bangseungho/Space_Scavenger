#include "Mineral.h"

OBJ* Mineral::_Obj = nullptr;

Mineral::Mineral()
{
	name = "Mineral";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj(filePath, "Mineral.obj");
	}

	obj = _Obj;
	level = 3;
}

Mineral::~Mineral()
{
}
