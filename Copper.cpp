#include "Copper.h"

OBJ* Copper::_Obj = nullptr;
Copper::Copper()
{
	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj(filePath, "Copper.obj");
	}
	obj = _Obj;
	name = "Copper";
	level = 3;
}

Copper::~Copper()
{

}