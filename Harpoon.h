#pragma once
#include "Equipment.h"

// todo 
// 자원 끌어오기 
// 플레이어 이동 및 변환시 함께 변환 = 우주선 작살 부착

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

public:
	double startTime;
	double endTime;
	int curEnergy;
	int chargedEnergy;
	float speed;
	const int maxEnergy = 3;
};

