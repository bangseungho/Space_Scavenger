#include "Cube.h"

VertexBlock* Cube::_Block = nullptr;

Cube::Cube() : Mesh(this)
{
	name = "Cube";

	if (_Block == nullptr)
	{
		_Block = new VertexBlock;
		ReadObj((char*)"Cube.obj", *_Block);
	}

	block = _Block;

	collider.tag = "Cube";
	collider.SetBox_OBB(vec3(2));
	collider.object = this;

	Render::meshtRender->AddObject(this, "Cube");
}

Cube::~Cube()
{
}