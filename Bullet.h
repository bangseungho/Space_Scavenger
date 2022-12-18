#pragma once
#include "Equipment.h"
#include "Object.h"
#include "ParticleGenerator.h"

// 총알을 새로 생성하지 않고 인덱스를 둬서 멀리 나가면 죽이고 죽인걸 다시 처음으로
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
	vec3 trajectory; // 궤적

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
