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
	void SerchResource();	// �ֺ��� Resource�� �ִ��� Ȯ��
	void GetData();
public:
	map<string, bool> resourceType;	// ������ �ڿ� ����Ʈ		(���� ������ �ڿ��� ���� ���� ����)
	float serchDistnace;	// ã�� �ڿ��� �ִ� ����

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