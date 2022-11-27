#pragma once
#include "Render.h"
#include "Collider.h"

class Cube :public Object, public Mesh
{
public:
	static VertexBlock* _Block;

public:
	Cube();
	~Cube();

public:
	void Init();
	void Update();

private:
	void MoveMent();

public:
	Collider collider;
};


