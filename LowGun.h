#pragma once
#include "Equipment.h"
#include "Object.h"
#include "Bullet.h"
#include "Sound.h"

class LowGun : public Equipment
{
	static OBJ* _Obj;

public:
	LowGun();
	~LowGun();

public:
	void Update();
	int Fire(const Transform& transform);
	void ReLoad();

public:
	vector<Bullet*> bullets;

private:
	int bulletNum;
	int fireCount;

private:
	Sound fireSound;
	Sound loadSound;
};
