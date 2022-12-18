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
	void InitPool(int _MaxCount, int _SpawnCount, float _DurationTime, Transform* _Target) { InitPool(_MaxCount, _SpawnCount, _DurationTime, _Target,100.0f,200.0f); };
	void InitPool(int _MaxCount, int _SpawnCount, float _DurationTime, Transform* _Target, float min, float max);
	void SetSapwnDistance(float min, float max);	// Sapwn min/max

private:
	void Spawn();
	void CheckDistance();

public:
	Transform* target_Transform;

private:
	ROS* pool;

	int maxCount;
	int spawnCount;

	Timer spawnTimer;

	float distanceMin, distanceMax;	// 활성화 된 obj가 스폰될 거리
};


