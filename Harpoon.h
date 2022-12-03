#pragma once
#include "Equipment.h"

class Harpoon : public Equipment
{
	static VertexBlock* _Block;

public:
	Harpoon();
	~Harpoon();

public:
	void Init();

	void ChargeEnergy();

	void Fire();
	void Update();

public:
	Transform* targetPos;
	bool firing = false;
	bool charging = false;

public:
	int strength = 0;
	int max_strength = 0;
	float speed = 100;
};

