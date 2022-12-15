#pragma once
#include "Equipment.h"
#include "Resource.h"
#include "Toggle.h"
#include "BackGround.h"
#include "ResourceData.h"

class Resource;

class Guidance : public Equipment
{
	class Wave : public Object, public Mesh
	{
	public:
		static OBJ* _Obj;
	public:
		Wave();
		~Wave();
	public:
		void Disable();
		void Update();
		mat4& SetMatrix();
	public:
		Resource* resource;
	};

public:
	static OBJ* _Obj;
public:
	Guidance();
	~Guidance();

public:
	void Enable();
	void Disable();
	void Init();
	void Update();

public:
	void SerchResource();	// 주변에 Resource가 있는지 확인
	void GetData();
public:
	map<string, bool> resourceType;	// 가져올 자원 리스트		(추후 설정된 자원만 끓고 오게 변경)
	float serchDistnace;	// 찾을 자원의 최대 범위

private:
	Sound sound_Dragged;
	Wave wave;
};

class GuidanceControl : public Object
{
public:
	GuidanceControl(Guidance* _Guidance);
	~GuidanceControl();

public:
	void Enable();
	void Disable();
	void Update();

public:
	Guidance* guidance;
private:
	BackGround background{"UI/BackGround/", "GuidanceBackground.png"};
	map<string, Toggle*> resourceToggles;
};