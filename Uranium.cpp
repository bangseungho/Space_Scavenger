#include "Uranium.h"
OBJ* Uranium::_Obj = nullptr;
int Uranium::amountData = -1;

Uranium::Uranium()
{
	name = "Uranium";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj(filePath, "Uranium.obj");
	}
	obj = _Obj;
	MeshInit();

	level = 3;

	collider.SetBox_OBB(vec3(obj->vBlock.max - obj->vBlock.min));

	if (amountData == -1)
	{
		amountData = sheet->readNum(1, 1);
	}
}

Uranium::~Uranium()
{
}
