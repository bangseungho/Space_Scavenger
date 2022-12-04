#include "Iron.h"

VertexBlock* Iron::_Block = nullptr;
int Iron::amountData = -1;

Iron::Iron()
{
	name = "Iron";

	if (_Block == nullptr)
	{
		_Block = new VertexBlock;
		ReadObj((char*)"Obj/Resource/Iron.obj", *_Block);	// 이름 변경 필수
	}

	block = _Block;

	collider.SetBox_OBB(vec3(2));

	if (amountData == -1)
	{
		amountData = sheet->readNum(1, 1);
	}
}

Iron::~Iron()
{
}
