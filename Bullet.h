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

public:
	Collider collider;
};
