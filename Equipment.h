#pragma once
#include "Render.h"
#include "Collider.h"
#include "Gauge.h"

class GuiObject;

class Equipment :public Object, public Mesh
{
public:
	static VertexBlock* _Block;

public:
	Equipment();
	~Equipment();

public:
	void Init();
	void Fire();
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


