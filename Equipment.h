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

public:
	Collider collider;
};


