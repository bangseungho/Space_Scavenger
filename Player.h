#pragma once
#include "PlayerData.h"
#include "Sound.h"
#include "Button.h"
#include "Quest.h"
#include "BackGround.h"

// Resource
#include "ResourcePool.cpp"
#include "Iron.h"
#include "Mineral.h"
#include "Emerald.h"
#include "Uranium.h"
#include "Gold.h"

// Equipment
#include "Harpoon.h"
#include "LowGun.h"
#include "Bullet.h"
#include "Guidance.h"

// UI
#include "SpeedGauge.h"

class QuestControl;
class UpgradeControl;

class Player : public Object, public Mesh
{
public:
	static Player* Instance;
	static OBJ* _Obj;

public:
	Player();
	~Player();

public:
	void Init();
	void Update();
	void Handle_Event(unsigned char key);
	void Handle_Event(int specialKey);
	void Handle_Event_Up(unsigned char key);
	void Handle_Event_Up(int specialKeyUp);
	void MyTimer();
	void OnCollision();

public:
	mat4& SetMatrix();
	void FaceMove(const vec2& diffPos);

private:
	void GetDate();

public:
	Collider collider;
	map<string, Equipment*> equipment;

public: // Upgrade 관련
	SpeedBlock speedBlock;
	map<wstring, int> resourceCount;

private:
	bool move_front;
	bool move_back;

private:
	UpgradeControl* upgrade;
	QuestControl* questControl;

private:	// 플레이어 주위에서 spawn 될 자원 pool
	ResourcePool<Iron> ironPool;
	ResourcePool<Gold> goldPool;
	ResourcePool<Mineral> mineralPool;
	ResourcePool<Emerald> emeraldlPool;
	//ResourcePool<Uranium> uraniumPool;

private:	// UI
	SpeedGauge speedGauge{ &speedBlock };
};

class UpgradeControl : public Object
{
public:
	UpgradeControl(Player* _Player);
	~UpgradeControl();
	
public:
	void Enable();
	void Disable();
	void Update();

public:
	Player* player;

private:
	BackGround background{ "UI/", "Frame.png"};
	map<string, Button> upgradeButtons;
};

class QuestControl : public Object {
public:
	QuestControl(Player* _Player);
	~QuestControl();

public:
	void Enable();
	void Disable();
	void Update();

private:
	void ClickQuestSeccse(wstring questName);
	void QuestReward(QuestNode* node);

private:
	Player* player;
	Quest quest;
	Button seccseButton;
	Toggle* nowToggle;
	map<wstring, Toggle*> questToggles;
};