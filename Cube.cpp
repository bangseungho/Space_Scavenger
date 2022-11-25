#include "Cube.h"

ObjectBlock* Cube::cube_Block = nullptr;

Cube::Cube()
{
	name = "Cube";

	if (cube_Block == nullptr)
	{
		cube_Block = new ObjectBlock;
		ReadObj((char*)"Cube.obj", *cube_Block);
	}

	block = cube_Block;

	collider.tag = "Cube";
	collider.SetBox_OBB(block->max - block->min);
	collider.object = this;
}

Cube::~Cube()
{
	delete cube_Block;
}

void Cube::Init()
{
	Object::Init();

	color.SetRandomColor();

	Render::objectRender->AddObject(this);
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