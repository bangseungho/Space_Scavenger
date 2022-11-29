#pragma once
#include "ResourcePool.cpp"
class ResourceGenerator : public Object
{
public:
	ResourceGenerator();
	~ResourceGenerator();

public:
	void Update();

public:
	void AddPool(ResourcePool<Resource>& pool);

public:
	vector<ResourcePool<Resource>*> poolList;
};

