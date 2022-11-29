#include "ResourcePool.h"

template<class ROS>
ResourcePool<ROS>::ResourcePool(int _MaxCount, int _SpawnCount, float _DurationTime)
	: maxCount(_MaxCount), spawnCount(_SpawnCount)
{
	pool = new ROS[_MaxCount];
	spawnTimer.durationTime = _DurationTime;
}

template<class ROS>
void ResourcePool<ROS>::Spawn()
{
	activeList.clear();
	int count = 0;
	for (int i = 0; i < maxCount; i++)
	{
		if (!pool[i].ActiveSelf())
			continue;

		pool[i].SetActive(true);
		activeList.push_back(pool[i]);

		if (++count >= spawnCount)
			continue;
	}
}
