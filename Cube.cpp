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
	collider.SetBox_OBB(block->max - block->min);
	collider.object = this;
}

Cube::~Cube()
{
	block = nullptr;
}

void Cube::Init()
{
	//Object::Init();

	color.SetRandomColor();

	Render::meshtRender->AddObject(this);
}

void Cube::Update()
{
	MoveMent();
}

void Cube::MoveMent()
{
	transform.worldPosition += worldSpeed * FrameTime::oneFrame;
	transform.worldRotation += worldRotateSpeed * FrameTime::oneFrame;
}