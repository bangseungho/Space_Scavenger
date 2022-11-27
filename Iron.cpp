#include "Iron.h"

VertexBlock* Iron::_Block = nullptr;

Iron::Iron()
{
	name = "Iron";

	if (_Block == nullptr)
	{
		_Block = new VertexBlock;
		//ReadObj((char*)"Cube.obj", *_Block);	// �̸� ���� �ʼ�
	}

	block = _Block;

	collider.SetBox_OBB(block->max);

}

Iron::~Iron()
{
}
