#pragma once
#include "Sound.h"
#include "Button.h"
#include "Quest.h"

// Resource
#include "ResourcePool.cpp"
#include "Iron.h"

// Equipment
#include "Harpoon.h"
#include "LowGun.h"
#include "Bullet.h"
#include "Guidance.h"

class UpgradeControl;

class Player : public Object, public Mesh
{
public:
	static Player* Instance;
	static OBJ* _Obj;

public:
	Player();
	~Player();

public:
	void Init();
	void Update();
	void Handle_Event(unsigned char key);
	void Handle_Event(int specialKey);
	void Handle_Event_Up(unsigned char key);
	void Handle_Event_Up(int specialKeyUp);
	void MyTimer();
	void OnCollision();

public:
	mat4& SetMatrix();
	void QuestHandle();
	void FaceMove(const vec2& diffPos);

public:
	Collider collider;
	map<string, Equipment*> equipment;

public: // Upgrade ����
	float speed = 10;

private:
	bool move_front;
	bool move_back;

private:
	UpgradeControl* upgrade;
	Quest quset;

private:	// �÷��̾� �������� spawn �� �ڿ� pool
	ResourcePool<Iron> ironPool;

};

class UpgradeControl : public Object
{
public:
	UpgradeControl(Player* _Player);
	~UpgradeControl();
	
public:
	void Update();

public:
	Player* player;

private:
	map<string, Button> upgradeButtons;
};