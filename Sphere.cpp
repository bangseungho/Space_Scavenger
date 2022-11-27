#include "Sphere.h"

VertexBlock* Sphere::sphere_Block = nullptr;

Sphere::Sphere() : Mesh(this)
{
	name = "Shpere";

	if (sphere_Block == nullptr)
	{
		sphere_Block = new VertexBlock;
		ReadObj((char*)"Sphere.obj", *sphere_Block);
	}

	block = sphere_Block;
}

Sphere::~Sphere()
{
}

void Sphere::Init()
{
	Object::Init();
	Render::meshtRender->AddObject(this);
}

void Sphere::MoveMent()
{
}

