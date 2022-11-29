#pragma once
#include "Object.h"
#include "Render.h"
#include "Collider.h"
class Resource : public Object, public Mesh
{
public:
	Resource();
	~Resource();

public:
	virtual void Init();

public:
	Collider collider;

private:
	unsigned int amount;
	vec3 velocity;
};