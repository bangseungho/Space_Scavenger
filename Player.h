#pragma once
#include "Collider.h"

#include "ResourcePool.cpp"
#include "Iron.h"
#include "Quest.h"
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

public:
	Collider collider;
	float speed = 10;

private:
	Quest quset;

private:	// �÷��̾� �������� spawn �� �ڿ� pool
	ResourcePool<Iron> ironPool;
};

