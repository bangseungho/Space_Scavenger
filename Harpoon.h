#pragma once
#include "Equipment.h"
#include "Gauge.h"

// todo 
// �ڿ� ������� 
// �÷��̾� �̵� �� ��ȯ�� �Բ� ��ȯ = ���ּ� �ۻ� ����
// �÷��̾�� ���� �̵��Ҷ� �̻��ϰ� �����̴� ���� -> �����̰� �߻��Ͽ��� �� 
// �� ������ �þ�� ����
// �� �����Ӵ� �����̴°� �ƴ� �ð��� �����̴°ɷ� �����ؾ��ҵ�

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

