#pragma once
#include "Equipment.h"
#include "Object.h"
#include "Bullet.h"
#include "Sound.h"
#include "BulletNum.h"

class LowGun : public Equipment
{
	static OBJ* _Obj;

public:
	LowGun();
	~LowGun();

public:
	void Enable();
	void Disable();
	void Update();

public:
	void Handle_Event();

public:
	int Fire(const Transform& transform);
	void ReLoad();

public:
	vector<Bullet*> bullets;
	int bulletNum;
	int bulletPower;

private:
	int fireCount;
	int remainBullet;

private:
	BulletNum* ui_bulletNum;

private:
	Sound fireSound;
	Sound loadSound;
};
