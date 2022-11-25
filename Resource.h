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
	unsigned int amount = 0;
	vec3 moveDirection = vec3(0);
};