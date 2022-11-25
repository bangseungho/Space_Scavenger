#pragma once
#include "Object.h"
#include "Render.h"

class Sphere : public Object
{
public:
	static ObjectBlock* sphere_Block;
public:
	Sphere();
	~Sphere();
public:
	void Init();

private:
	void MoveMent();
};

