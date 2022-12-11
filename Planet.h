#pragma once
#include "Light.h"
class Planet : public Object, public Mesh
{
public:
	Planet(string objName);
	~Planet();

private:
	Light light;
};

