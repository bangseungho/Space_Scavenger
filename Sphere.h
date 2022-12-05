#pragma once
#include "Render.h"

class Sphere : public Object, public Mesh
{
public:
	static OBJ* _Obj;
public:
	Sphere();
	~Sphere();
};

