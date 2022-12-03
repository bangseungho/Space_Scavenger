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
	void Handle_Evnet(int specialKey);
	void FireSet();

public:
	Collider collider;
<<<<<<< HEAD

=======
	int strength = 0;
	int max_strength = 0;
	float speed = 100;
	bool firing = false;
	bool charging = false;

public:
>>>>>>> main
};


