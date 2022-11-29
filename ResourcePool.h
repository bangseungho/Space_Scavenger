#pragma once
#include "Resource.h"
#include "Timer.h"

template <class ROS>
class ResourcePool : public Object
{
public:
	ResourcePool(int _MaxCount, int _SpawnCount, float _DurationTime);
	~ResourcePool();

public:
	void Spawn();

public:
	vector<ROS*> activeList;	// Spawn�� ���� Ȱ��ȭ �� obj

private:
	ROS* pool;

	int maxCount;
	int spawnCount;
	Timer spawnTimer;
};


