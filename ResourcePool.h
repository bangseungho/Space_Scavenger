#pragma once
#include "Resource.h"
#include "Timer.h"

template <class ROS>
class ResourcePool : public Object
{
public:
	ResourcePool(int _MaxCount, int _SpawnCount, float _DurationTime, Transform* _Target);
	~ResourcePool();

public:
	void Update();
	void Spawn(float _Min, float _Max);

public:
	Transform* target_Transform;
	float distance_Min, distance_Max;	// Ȱ��ȭ �� obj�� ������ �Ÿ�

private:
	ROS* pool;

	int maxCount;
	int spawnCount;
	Timer spawnTimer;
};


