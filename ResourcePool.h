#pragma once
#include "Resource.h"
#include "Timer.h"

template <class ROS, int _MaxCount>
class ResourcePool : public Object
{
public:
	ResourcePool();
	ResourcePool(int _SpawnCount, float _DurationTime);
	~ResourcePool();

public:
	void Init();
	void Update();
	void Spawn();

public:
	ROS pool[_MaxCount];

private:
	int spawnCount;
	Timer spawnTimer;
};


