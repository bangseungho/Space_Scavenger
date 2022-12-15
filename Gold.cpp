#include "Gold.h"

OBJ* Gold::_Obj = nullptr;
int Gold::amountData = -1;

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

	collider.SetBox_OBB(vec3(obj->vBlock.max - obj->vBlock.min));

	if (amountData == -1)
	{
		amountData = sheet->readNum(1, 1);
	}
}

Gold::~Gold()
{

}
