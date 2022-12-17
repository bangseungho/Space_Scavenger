#include "Gold.h"

OBJ* Gold::_Obj = nullptr;

Gold::Gold()
{
	name = "Gold";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj(filePath, "Gold.obj");
	}

	obj = _Obj;
	level = 3;
}

Gold::~Gold()
{

}
