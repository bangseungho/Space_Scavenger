#pragma once
#include "Collider.h"
#include "Equipment.h"
#include "ResourcePool.cpp"
#include "Iron.h"
#include "Quest.h"
#include "Harpoon.h"
#include "LowGun.h"
#include "Bullet.h"
#include "Guidance.h"

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
	Equipment* equipment;

public:
	float speed = 10;
	bool move_front;
	bool move_back;

private:
	Quest quset;

private:	// 플레이어 주위에서 spawn 될 자원 pool
	ResourcePool<Iron> ironPool;

};

