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

	block.vertIndex = cube_Block->vertIndex;
	block.faceIndex = cube_Block->faceIndex;
	block.vertices = cube_Block->vertices;
	block.face = cube_Block->face;
}

Cube::~Cube()
{
}

void Cube::Update()
{
	MoveMent();
	SetMatrix();
}

void Cube::Init()
{
	Object::Init();

	color.SetRandomColor();
	collider.InitTransform(transform);
	collider.SetBox(block.vertices);
	collider.tag = "Object";

	Render::mainRender->AddObject(this);
}

void Cube::MoveMent()
{
	transform.worldPosition += worldSpeed * FrameTime::oneFrame;
	transform.worldRotation += worldRotateSpeed * FrameTime::oneFrame;
}