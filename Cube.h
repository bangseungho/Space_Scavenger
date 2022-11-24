#pragma once
#include "Render.h"
#include "Collider.h"

class Cube :public Object
{
public:
	static ObjectBlock* cube_Block;

public:
	Cube();
	~Cube();

public:
	void Init();
	void Update();
	void Collision();

private:
	void MoveMent();

public:
	Collider collider;
};


