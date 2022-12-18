#pragma once
#include "Star.h"

// Planet Contain
#include "Earth.h"
#include "Moon.h"
#include "Saturn.h"

class PlanetManager : public Object
{
public:
	PlanetManager() : PlanetManager(5000,15000) {};
	PlanetManager(int frist, int second);
	~PlanetManager();

public:
	void Init();
private:
	Star sun;

	Earth earth;
	Moon moon;
	Saturn saturn;
};

