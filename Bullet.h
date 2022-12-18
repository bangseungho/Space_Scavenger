#pragma once
#include "Equipment.h"
#include "Object.h"
#include "ParticleGenerator.h"

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

public:
	Collider collider;

public:
	float distance;

private:
	Sound sound_Hit;

	const int range = 200;

private:
	ParticleGenerator* particle;

};
