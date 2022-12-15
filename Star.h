#pragma once
#include "Light.h"

class Star : public Object, public Mesh
{
public:
	Star(string objName);
	~Star();

public:
	void Init();
	void Update();

private:
	Light light;
};

