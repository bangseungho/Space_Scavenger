#pragma once
#include "Sound.h"
#include "Render.h"
#include "Collider.h"
#include "Gauge.h"

enum class EqType {
	HARPOON,	// �ۻ�
	LOWGUN,		// ��
	BULLET,		// �Ѿ�
	GUIDANCE,	// ����
};

enum class State {
	IDLE,
	CHARGING,
	FIRING,
};

class Equipment :public Object, public Mesh
{
public:
	Equipment();
	~Equipment();

public:
	void SetType(EqType type);
	EqType GetType();
	void SetState(State state);
	State GetState();
	mat4& SetMatrix();

public:
	virtual void Init();
	virtual void Update();
	void Handle_Evnet(int specialKey);

public:
	int strength = 0;
	int max_strength = 0;
	float speed = 100;
	bool firing = false;
	bool charging = false;
	bool isDragged; // ���� �ڿ��� ������� �ִ��� üũ
	bool isUnLock;	// �� ������ ����� �� �ִ����� ���� ����
	Transform targetPos;

protected:
	EqType myType;
	State myState;
};


