#include "PlanetManager.h"

PlanetManager::PlanetManager(int frist, int second)
{
	sun.transform.local->position.x = RandomInt(frist, second) * RandomPlusMinus();
	sun.transform.local->position.y = RandomInt(frist, second) * RandomPlusMinus();
	sun.transform.local->position.z = RandomInt(frist, second) * RandomPlusMinus();
	sun.color.SetRandomColor();
	sun.color.G = RandomInt(1, 5);
	sun.color.B = RandomInt(1, 5);

	earth.color.SetRandomColor();
	earth.transform.local->position = RandomVEC3(vec3(5500, 2000, 2200), vec3(12000, 3000, 5500));

	moon.color.SetRandomColor();
	moon.transform.local->scale = vec3(RandomInt(1, 3));
	moon.transform.local->position = RandomVEC3(vec3(1500, 200, 700), vec3(5000, 2000, 2000));

	saturn.color.SetRandomColor();
	saturn.transform.local->position = RandomVEC3(vec3(1300, 5000, -2200), vec3(32000, 10000, -1000));
}

PlanetManager::~PlanetManager()
{
}

void PlanetManager::Init()
{
	for (auto& world : sun.transform.world)
	{
		earth.transform.world.push_back(world);
		moon.transform.world.push_back(world);
		saturn.transform.world.push_back(world);
	}
	TransformBlock* local = sun.transform.local;
	earth.transform.world.push_back(local);
	moon.transform.world.push_back(local);
	saturn.transform.world.push_back(local);
}
