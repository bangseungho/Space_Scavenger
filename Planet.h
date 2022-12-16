#pragma once
#include "Render.h"
class Planet : public Object, public Mesh
{
public:
	Planet();
	~Planet();

public:
	virtual void Update();
};

