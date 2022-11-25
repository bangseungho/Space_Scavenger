#pragma once
#include "Object.h"
#include "Collider.h"
class Resource : public Object
{
public:
	Resource();
	~Resource();

public:


public:
	Collider collider;

private:
	unsigned int amount;
	vec3 moveDirection;
};