#pragma once
#include "Equipment.h"
#include "Gauge.h"

// todo 
// 자원 끌어오기 
// 플레이어 이동 및 변환시 함께 변환 = 우주선 작살 부착
// 플레이어와 같이 이동할때 이상하게 움직이는 버그 -> 움직이고 발사하였을 때 
// 양 축으로 늘어나는 버그
// 한 프레임당 움직이는게 아닌 시간당 움직이는걸로 수정해야할듯

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
	void OnCollision();

public:
	Collider collider;

public:
	Gauge* gauge;

public:
	double startTime;
	double endTime;
	double chargingTime;
	int curEnergy; 
	int chargedEnergy;
	float speed;
	const unsigned int maxEnergy = 2;
};

