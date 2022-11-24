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

	block.vertices = cube_Block->vertices;
	block.vertices_uvs = cube_Block->vertices_uvs;
	block.vertices_normals = cube_Block->vertices_normals;

	block.vertexIndices = cube_Block->vertexIndices;
	block.uvIndices = cube_Block->uvIndices;
	block.normalIndices = cube_Block->normalIndices;

	block.max = cube_Block->max;

	collider.tag = "Cube";
	collider.SetBox_OBB(block.max);
	collider.object = this;
}

Cube::~Cube()
{
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

void Cube::Collision()
{
	for (const auto& other : Collider::allCollider)
	{
	}
}

void Cube::MoveMent()
{
	transform.worldPosition += worldSpeed * FrameTime::oneFrame;
	transform.worldRotation += worldRotateSpeed * FrameTime::oneFrame;
}