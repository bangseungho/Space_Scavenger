#include "Iron.h"

OBJ* Iron::_Obj = nullptr;

Iron::Iron()
{
	name = "Iron";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj(filePath, "Iron.obj");	// 이름 변경 필수
	}
	obj = _Obj;

	level = 3;
}

Iron::~Iron()
{
}
