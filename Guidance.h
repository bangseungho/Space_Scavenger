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

public:
	void SerchResource();	// �ֺ��� Resource�� �ִ��� Ȯ��
public:
	map<string, bool> resourceType;	// ������ �ڿ� ����Ʈ		(���� ������ �ڿ��� ���� ���� ����)

public:
	float serchDistnace;	// ã�� �ڿ��� �ִ� ����
};

