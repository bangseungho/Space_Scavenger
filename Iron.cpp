#include "Iron.h"

ObjectBlock* Iron::_Block = nullptr;

Iron::Iron()
{
	name = "Iron";

	if (_Block == nullptr)
	{
		_Block = new ObjectBlock;
		//ReadObj((char*)"Cube.obj", *_Block);	// �̸� ���� �ʼ�
	}

	block = _Block;

	collider.SetBox_OBB(block->max);

}

Iron::~Iron()
{
}
