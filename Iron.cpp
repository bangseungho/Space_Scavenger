#include "Iron.h"

ObjectBlock* Iron::_Block = nullptr;

Iron::Iron()
{
	name = "Iron";

	if (_Block == nullptr)
	{
		_Block = new ObjectBlock;
		//ReadObj((char*)"Cube.obj", *_Block);	// 이름 변경 필수
	}

	block = _Block;

	collider.SetBox_OBB(block->max);

}

Iron::~Iron()
{
}
