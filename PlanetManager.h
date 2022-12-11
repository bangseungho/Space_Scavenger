#pragma once
#include "Planet.h"

class PlanetManager : public Object
{
public:
	PlanetManager();
	~PlanetManager();

public:


private:
	Planet earth{"Earth.obj"};
	Planet moon{"Moon.obj"};
	Planet saturn{"Saturn.obj"};
	Planet sun{"Sun.obj"};
};

