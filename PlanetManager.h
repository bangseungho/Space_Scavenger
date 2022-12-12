#pragma once
#include "Planet.h"
#include "Star.h"

class PlanetManager : public Object
{
public:
	PlanetManager();
	~PlanetManager();

public:


private: // Planet
	Planet earth{"Earth.obj"};
	Planet moon{"Moon.obj"};
	Planet saturn{"Saturn.obj"};

private: //Star
	Star sun{"Sun.obj"};
};

