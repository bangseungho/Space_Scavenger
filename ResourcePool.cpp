#include "ResourcePool.h"

template<class ROS, int _MaxCount>
ResourcePool<ROS, _MaxCount>::ResourcePool()
{
}

template <class ROS, int _MaxCount>
inline ResourcePool<ROS, _MaxCount>::ResourcePool(int _SpawnCount, float _DurationTime)
{
	spawnCount = _SpawnCount;
	spawnTimer.durationTime = _DurationTime;
}

template <class ROS, int _MaxCount>
ResourcePool<ROS, _MaxCount>::~ResourcePool()
{
}

template <class ROS, int _MaxCount>
void ResourcePool<ROS, _MaxCount>::Init()
{
}

template <class ROS, int _MaxCount>
void ResourcePool<ROS, _MaxCount>::Update()
{
}

template<class ROS, int _MaxCount>
void ResourcePool<ROS, _MaxCount>::Spawn()
{
	int count = 0;
	for (int i = 0; i < _MaxCount; i++)
	{
		if (!pool[i].ActiveSelf())
			continue;

		pool[i].SetActive(trues);

		if (++count >= spawnCount)
			continue;
	}
}
