#pragma once
#include "Render.h"
class Planet : public Object, public Mesh
{
public:
	Planet(string objName);
	~Planet();

public:
	void Update();
};

