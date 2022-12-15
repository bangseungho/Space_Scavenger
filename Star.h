#pragma once
#include "Light.h"

class Star : public Object, public Mesh
{
public:
	static OBJ* _Obj;
public:
	Star();
	~Star();

public:
	void Init();
	void Update();

private:
	Light light;
};

