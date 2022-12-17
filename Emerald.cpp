#include "Emerald.h"

OBJ* Emerald::_Obj = nullptr;

Emerald::Emerald()
{
	name = "Emerald";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj(filePath, "Emerald.obj");
	}

	obj = _Obj;
	level = 3;

}

Emerald::~Emerald()
{
}
