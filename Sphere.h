#pragma once
#include "Render.h"

class Sphere : public Object, public Mesh
{
public:
	static VertexBlock* sphere_Block;
public:
	Sphere();
	~Sphere();
public:
	void Init();

private:
	void MoveMent();
};

