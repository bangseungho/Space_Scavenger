#pragma once
#include "Resource.h"
#include "Timer.h"

template <class ROS>
class ResourcePool : public Object
{
public:
	ResourcePool() {};
	ResourcePool(int _MaxCount, int _SpawnCount, int _level, float _DurationTime, Transform* _Target);
	~ResourcePool();

public:
	void Update();
	void Spawn(float _Min, float _Max);

public:
	void InitPool(int _MaxCount, int _SpawnCount, int _level, float _DurationTime, Transform* _Target);

public:
	Transform* target_Transform;
	float distance_Min, distance_Max;	// Ȱ��ȭ �� obj�� ������ �Ÿ�

private:
	ROS* pool;

	int maxCount;
	int spawnCount;
	int level;

	Timer spawnTimer;
};


