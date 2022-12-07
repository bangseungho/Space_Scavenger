#pragma once
#include "Equipment.h"
#include "Object.h"
#include "Bullet.h"

class LowGun : public Equipment
{
	static OBJ* _Obj;

public:
	LowGun();
	~LowGun();

public:
	void Update();
	void Fire();

public:
	Bullet bullet;

};
