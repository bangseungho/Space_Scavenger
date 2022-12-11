#include "Mineral.h"

OBJ* Mineral::_Obj = nullptr;
int Mineral::amountData = -1;

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

	collider.SetBox_OBB(vec3(obj->vBlock.max - obj->vBlock.min));

	if (amountData == -1)
	{
		amountData = sheet->readNum(1, 1);
	}
}

Mineral::~Mineral()
{
}
