#pragma once
#include "Render.h"
#include "Collider.h"
#include "Gauge.h"

enum class EqType {
	HARPOON,
	NET,
	GUIDANCE, // ����
};

enum class State {
	IDLE,
	CHARGING,
	FIRING,
};

class Equipment :public Object, public Mesh
{
public:
	Equipment();
	~Equipment();

public:
	virtual void ChargingEnergy();
	virtual void FinishCharging();

public:
	void SetType(EqType type);
	EqType GetType();
	void SetState(State state);
	State GetState();

public:
	void Init();
	void Update();
	void Handle_Evnet(int specialKey);
	void FireSet();

public:
	Collider collider;

	int strength = 0;
	int max_strength = 0;
	float speed = 100;
	bool firing = false;
	bool charging = false;

protected:
	EqType myType;
	State myState;
};


