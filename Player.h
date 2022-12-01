#pragma once
#include "Collider.h"

#include "ResourcePool.cpp"
#include "Iron.h"
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

private: // MouseEvent
	//void MouseWheelEvent(int wheel, int direction, vec2 pos);

public:
	Collider collider;
	float speed = 1;
private:	// 플레이어 주위에서 spawn 될 자원 pool
	ResourcePool<Iron> ironPool;
};

