#pragma once
#include "Resource.h"
#include "Timer.h"

template <class ROS>
class ResourcePool : public Object
{
public:
	ResourcePool() { maxCount = 0; };
	ResourcePool(int _MaxCount, int _SpawnCount, float _DurationTime, Transform* _Target);
	~ResourcePool();

public:
	void Update();

public:
	void InitPool(int _MaxCount, int _SpawnCount, float _DurationTime, Transform* _Target);

private:
	void Spawn(float _Min, float _Max);
	void CheckDistance();

public:
	Transform* target_Transform;
	float distance_Min, distance_Max;	// 활성화 된 obj가 스폰될 거리

private:
	ROS* pool;

	int maxCount;
	int spawnCount;

	Timer spawnTimer;
};


