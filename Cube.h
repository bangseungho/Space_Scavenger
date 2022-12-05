#pragma once
#include "Render.h"
#include "Collider.h"

class Cube :public Object, public Mesh
{
public:
	static OBJ* _Obj;

public:
	Cube();
	~Cube();

public:
	Collider collider;
};


