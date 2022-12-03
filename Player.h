#pragma once
#include "Collider.h"

#include "Equipment.h"
#include "ResourcePool.cpp"
#include "Iron.h"
#include "Quest.h"
#include "Harpoon.h"

class Player : public Object, public Mesh
{
public:
	static Player* Instance;
	static VertexBlock* _Block;

public:
	Player();
	~Player();

public:
	void Init();
	void Update();
	void Handle_Evnet(unsigned char key);
	void Handle_Evnet(int specialKey);
	void OnCollision();

public:
	mat4& SetMatrix();
	void QuestHandle();
	void FaceMove(const vec2& diffPos);

public:
	Collider collider;
	Equipment equipment;

public:
	float speed = 10;

private:

	Quest quset;

private:	// 플레이어 주위에서 spawn 될 자원 pool
	ResourcePool<Iron> ironPool;
	Equipment* equipment;
};

