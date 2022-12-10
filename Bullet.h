#pragma once
#include "Equipment.h"
#include "Object.h"

// �Ѿ��� ���� �������� �ʰ� �ε����� �ּ� �ָ� ������ ���̰� ���ΰ� �ٽ� ó������
class Bullet : public Equipment
{
	static OBJ* _Obj;

public:
	Bullet();
	~Bullet();

public:
	void Update();
	void OnCollision();
	float getDistance();

public:
	vec3 trajectory; // ����
	vec3 gunPos;

public:
	Collider collider;

public:
	float distance;
	bool isUse;

private:
	const int range = 200;
};
