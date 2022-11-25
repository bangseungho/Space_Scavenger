#include "Sphere.h"

ObjectBlock* Sphere::sphere_Block = nullptr;

Sphere::Sphere()
{
	name = "Shpere";

	if (sphere_Block == nullptr)
	{
		sphere_Block = new ObjectBlock;
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
	Render::objectRender->AddObject(this);
}

void Sphere::MoveMent()
{
}

