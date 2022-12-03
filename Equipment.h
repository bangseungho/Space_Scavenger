#pragma once
#include "Render.h"
#include "Collider.h"
#include "Gauge.h"

enum class EqType {
	HARPOON,
	NET,
	MAGNETIC,
};

enum class State {
	IDLE,
	CHARGING,
	FIRING,
};

class Equipment :public Object, public Mesh
{
private:
	EqType myType;
	State myState;

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

public:
	Collider collider;

};


