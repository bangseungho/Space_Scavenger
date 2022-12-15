#include "Emerald.h"

OBJ* Emerald::_Obj = nullptr;
int Emerald::amountData = -1;

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

	collider.SetBox_OBB(vec3(obj->vBlock.max - obj->vBlock.min));

	if (amountData == -1)
	{
		amountData = sheet->readNum(1, 1);
	}
}

Emerald::~Emerald()
{
}
