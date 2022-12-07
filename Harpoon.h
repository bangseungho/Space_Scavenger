#pragma once
#include "Equipment.h"

class Harpoon : public Equipment
{
	static OBJ* _Obj;

public:
	Harpoon();
	~Harpoon();

public:
	void Init();
	void Update();
	void ChargingEnergy();
	void FinishCharging();
	void MyTimer();
	void Fire();
public:
	Collider collider;
	Transform* targetPos;

public:
	double startTime;
	double endTime;
	int curEnergy;
	int chargedEnergy;
	float speed;
	const int maxEnergy = 3;
};

