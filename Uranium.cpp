#include "Uranium.h"
OBJ* Uranium::_Obj = nullptr;
Uranium::Uranium()
{
	name = "Uranium";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj(filePath, "Uranium.obj");
	}

	obj = _Obj;
	level = 3;
}

Uranium::~Uranium()
{
}
