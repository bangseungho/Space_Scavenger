#include "Moon.h"

OBJ* Moon::_Obj = nullptr;

Moon::Moon()
{
	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Planet/", "Moon.obj");
	}
	obj = _Obj;

	name = "Moon";
}

Moon::~Moon()
{
}
