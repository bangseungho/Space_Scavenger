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
	int Fire(const Transform& transform);
	void ReLoad();

public:
	vector<Bullet*> bullets;

private:
	int bulletNum;
	int fireCount;
	int remainBullet;

private:
	BulletNum* ui_bulletNum;

private:
	Sound fireSound;
	Sound loadSound;

};
