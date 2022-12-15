#include "PlanetManager.h"

PlanetManager::PlanetManager()
{
	//earth.transform.local->position.x = 1000;
	//blueEarth.transform.local->scale *= 1.4;
	//blueEarth.transform.local->position.x = 2000;
	//blueEarth.color.SetColor({ 0,0,1,1 });
	//moon.transform.local->position.y = 3000;
	//yellowMoon.transform.local->scale *= 3;
	//yellowMoon.transform.local->position.x = 7000;
	//yellowMoon.color.SetColor({ 1,1,0,1 });
	//saturn.transform.local->position.x = 4000;
	//int i = 0;
	//for (Star& sun : suns)
	//{
	//	sun.transform.local->position.x = 2000 * i++;
	//	sun.transform.local->position.y = 1000;
	//	sun.transform.local->position.z = 1000;
	//	sun.color.R = RandomFloat(0, 1);
	//	sun.color.G += RandomInt(1, 10);
	//	sun.color.B += RandomInt(1, 10);
	//}

	//earth.transform.local->position.x = 10000;
	//blueEarth.transform.local->scale *= 1.4;
	//blueEarth.transform.local->position.x = 5000;
	//blueEarth.transform.local->position.y = 5000;
	//blueEarth.color.SetColor({ 0,0,1,1 });
	//moon.transform.local->position.x = -10000;
	//yellowMoon.transform.local->scale *= 30;
	//yellowMoon.transform.local->position.y = -10000;
	//yellowMoon.transform.local->position.z = 30000;
	//yellowMoon.color.SetColor({ 1,1,0,1 });
	//saturn.transform.local->position.y = 10000;

	for (Star& sun : suns)
	{
		sun.transform.local->position.x = RandomInt(5000, 15000) * RandomPlusMinus();
		sun.transform.local->position.y = RandomInt(5000, 15000) * RandomPlusMinus();
		sun.transform.local->position.z = RandomInt(5000, 15000) * RandomPlusMinus();
		sun.color.SetRandomColor();
		sun.color.G = RandomInt(1, 5);
		sun.color.B = RandomInt(1, 5);
	}
	suns[0].color.SetColor({ 1,1,1,1 });
}

PlanetManager::~PlanetManager()
{
}
