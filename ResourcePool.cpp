#include "ResourcePool.h"

template<class ROS>
ResourcePool<ROS>::ResourcePool(int _MaxCount, int _SpawnCount, int _level, float _DurationTime, Transform* _Target)
	: maxCount(_MaxCount), spawnCount(_SpawnCount), level(_level)
{
	pool = new ROS[_MaxCount];
	spawnTimer.durationTime = _DurationTime;
	target_Transform = _Target;
	distance_Min = distance_Max = 10;	// 임시
}

template<class ROS>
ResourcePool<ROS>::~ResourcePool()
{
}

template<class ROS>
void ResourcePool<ROS>::Update()
{
	if (!spawnTimer.CheckTimer())
		return;

	Spawn(distance_Min, distance_Max);
}

template<class ROS>
void ResourcePool<ROS>::Spawn(float _Min, float _Max)
{
	int count = 0;
	for (int i = 0; i < maxCount; i++)
	{
		if (pool[i].ActiveSelf())
			continue;

		float dis = RandomFloat(_Min, _Max);
		float radian = radians(RandomFloat(0, 360));
		vec3 pos{ dis * sin(radian), dis * cos(radian), dis * tan(radian) };
		pool[i].transform.worldPosition = pos + target_Transform->worldPosition;
		pool[i].SetActive(true);

		if (++count >= spawnCount)
			break;
	}
}

template<class ROS>
void ResourcePool<ROS>::InitPool(int _MaxCount, int _SpawnCount, int _level, float _DurationTime, Transform* _Target)
{
	pool = new ROS[_MaxCount];
	maxCount = _MaxCount;
	spawnCount = _SpawnCount;
	level = _level;

	spawnTimer.durationTime = _DurationTime;
	target_Transform = _Target;

	distance_Min = distance_Max = 10;	// 임시
}
