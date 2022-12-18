#include "ResourcePool.h"

template<class ROS>
ResourcePool<ROS>::ResourcePool(int _MaxCount, int _SpawnCount, float _DurationTime, Transform* _Target)
	: maxCount(_MaxCount), spawnCount(_SpawnCount)
{
	pool = new ROS[_MaxCount];
	spawnTimer.durationTime = _DurationTime;
	target_Transform = _Target;
	distanceMin = distanceMax = 100;	// юс╫ц
}

template<class ROS>
ResourcePool<ROS>::~ResourcePool()
{
}

template<class ROS>
void ResourcePool<ROS>::Update()
{
	CheckDistance();
	if (!spawnTimer.CheckTimer())
		return;

	Spawn();
}

template<class ROS>
void ResourcePool<ROS>::Spawn()
{
	int count = 0;
	for (int i = 0; i < maxCount; i++)
	{
		if (pool[i].ActiveSelf())
			continue;

		float dis = RandomFloat(distanceMin, distanceMax);
		float radian = radians(RandomFloat(0, 360));
		vec3 pos{ dis * sin(radian), dis * cos(radian), dis * tan(radian) };
		pool[i].transform.local->position = pos + target_Transform->local->position;
		pool[i].SetActive(true);

		if (++count >= spawnCount)
			break;
	}
}

template<class ROS>
void ResourcePool<ROS>::InitPool(int _MaxCount, int _SpawnCount, float _DurationTime, Transform* _Target, float min, float max)
{
	pool = new ROS[_MaxCount];
	maxCount = _MaxCount;
	spawnCount = _SpawnCount;

	spawnTimer.durationTime = _DurationTime;
	target_Transform = _Target;

	distanceMin = min;
	distanceMax = max;
}

template<class ROS>
void ResourcePool<ROS>::CheckDistance()
{
	for (int i = 0; i < maxCount; i++)
	{
		if (!pool[i].ActiveSelf())
			continue;

		if (pool[i].isDragged)
			continue;

		float dis = length((target_Transform->model - pool[i].transform.model) * vec4(0,0,0,1));

		if (dis > distanceMax + 1000)
			pool[i].SetActive(false);
	}
}
