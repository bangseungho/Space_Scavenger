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
	void SerchResource();	// 주변에 Resource가 있는지 확인
public:
	map<string, bool> resourceType;	// 가져올 자원 리스트		(추후 설정된 자원만 끓고 오게 변경)
	float serchDistnace;	// 찾을 자원의 최대 범위

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