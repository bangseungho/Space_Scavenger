#pragma once
#include "Equipment.h"
#include "Resource.h"

// todo 
// event �Լ��� ���� collide�� �ɸ� �ڿ��� drag�� ų �� �ְ� �ؾ���

class Guidance : public Equipment
{
public:
	Guidance();
	~Guidance();

public:
	void Update();
	void OnCollision();

public:
	void SerchResource();	// �ֺ��� Resource�� �ִ��� Ȯ��
public:
	Collider collider;

	map<string, bool> resourceType;

public:
	float serchDistnace;
};

