#pragma once
#include "Equipment.h"
#include "Resource.h"
#include "Toggle.h"
#include "BackGround.h"
#include "ResourceData.h"

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
	float serchDistnace;	// ã�� �ڿ��� �ִ� ����

private:
	Sound sound_Dragged;
};

class GuidacnePopUp : public Object
{
public:
	GuidacnePopUp(Guidance* _Guidance);
	~GuidacnePopUp();

public:
	void Enable();
	void Disable();

public:
	Guidance* guidance;
private:
	//BackGround background;
	map<string, Toggle> resourceToggles;
};