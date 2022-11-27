#pragma once
#include "Resource.h"

class ResourcePool : public Object
{
public:
	ResourcePool();
	~ResourcePool();

public:
	void Init();
	void Update();
};

