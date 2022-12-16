#pragma once
#include "Star.h"

// Planet Contain
#include "Earth.h"

class PlanetManager : public Object
{
public:
	PlanetManager();
	~PlanetManager();

public:
	void Init();
private:
	Star sun;

	Earth earth;
};

