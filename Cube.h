#pragma once
#include "Collider.h"
#include "Render.h"

class Cube :public Object
{
public:
	static ObjectBlock* cube_Block;

public:
	Cube();
	~Cube();

public:
	void Update();
	void Init();

private:
	void MoveMent();

public:
	Collider collider;

	float yScaleSpeed = 0;
};


