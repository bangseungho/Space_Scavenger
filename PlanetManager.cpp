#include "PlanetManager.h"

PlanetManager::PlanetManager()
{
	earth.transform.local->position.x = 10000;
	moon.transform.local->position.x = -10000;
	saturn.transform.local->position.y = 10000;
	sun.transform.local->position.z = -10000;
}

PlanetManager::~PlanetManager()
{
}
