#include "Iron.h"

VertexBlock* Iron::_Block = nullptr;

Iron::Iron()
{
	name = "Iron";

	if (_Block == nullptr)
	{
		_Block = new VertexBlock;
		//ReadObj((char*)"Cube.obj", *_Block);	// 이름 변경 필수
	}

	block = _Block;

	collider.SetBox_OBB(block->max);

}

Iron::~Iron()
{
}
