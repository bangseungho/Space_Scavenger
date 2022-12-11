#include "PlanetManager.h"

PlanetManager::PlanetManager()
{
	earth.transform.local->position.x = 100;
	moon.transform.local->position.x = -100;
	saturn.transform.local->position.y = 100;
	sun.transform.local->position.z = -100;
}

PlanetManager::~PlanetManager()
{
}
