#include "Iron.h"

OBJ* Iron::_Obj = nullptr;
int Iron::amountData = -1;

Iron::Iron()
{
	name = "Iron";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Resource/", "Iron.obj");	// 이름 변경 필수
	}

	obj = _Obj;
	level = 3;

	collider.SetBox_OBB(vec3(2));

	if (amountData == -1)
	{
		amountData = sheet->readNum(1, 1);
	}
}

Iron::~Iron()
{
}
