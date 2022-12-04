#pragma once
#include "Equipment.h"
#include "Resource.h"

// todo 
// event 함수를 통해 collide에 걸린 자원이 drag를 킬 수 있게 해야함

class Guidance : public Equipment
{
public:
	Guidance();
	~Guidance();

public:
	void Update();
	void OnCollision();

public:
	void SerchResource();	// 주변에 Resource가 있는지 확인
public:
	Collider collider;

	map<string, bool> resourceType;

public:
	float serchDistnace;
};

