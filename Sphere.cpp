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

	Render::meshtRender->AddObject(this, "Sphere");
}

Sphere::~Sphere()
{
}