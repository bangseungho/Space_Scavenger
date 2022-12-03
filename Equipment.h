#pragma once
#include "Render.h"
#include "Collider.h"
#include "Gauge.h"

enum class EqType {
	HARPOON,
	NET,
	MAGNETIC,
};

class Equipment :public Object, public Mesh
{
private:
	EqType myType;

public:
	void SetType(EqType type);
	EqType GetType();

public:
	Equipment();
	~Equipment();

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

public:
};


