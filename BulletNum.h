#pragma once
#include "Render.h"
#include "Font.h"

#pragma region Image
class IconBullet : public Object, public UIMesh
{
public:
	IconBullet() : UIMesh(this) {
		SetActive(false);
		Render::uiRender->AddObject(this);
	}
};

class EmptyBullet : public Object, public UIMesh
{
public:
	EmptyBullet() : UIMesh(this) {
		SetActive(false);
		Render::uiRender->AddObject(this);
	}
};

class FullBullet : public Object, public UIMesh
{
public:
	FullBullet() : UIMesh(this) {
		SetActive(false);
		Render::uiRender->AddObject(this);
	}

public:
	static int totalNum;
	static int rad;
};

class Reload: public Object, public UIMesh
{
public:
	Reload() : UIMesh(this) {
		SetActive(false);
		Render::uiRender->AddObject(this);
	}

public:
	static int totalNum;
	static int rad;
};

class IconLowGun : public Object, public UIMesh
{
public:
	IconLowGun() : UIMesh(this) {
		SetActive(false);
		transform.local->position.x += 180;
		transform.local->position.y -= 20;
		Render::uiRender->AddObject(this);
	}

public:
	static int totalNum;
	static int rad;
};
#pragma endregion

class BulletNum : public Object
{
public:
	BulletNum() : BulletNum("UI/Equipment/Bullet/") {};
	BulletNum(string path);
	~BulletNum();

public:
	void Enable();
	void Disable();
	void Init();
	void Update();

public:
	void GetBulletInfo(const int& _BulletNum, const int& _RemainBullet);

public:
	Font font;
	Color color;

private:
	IconBullet ui_Icon;
	EmptyBullet ui_Empty;
	Reload ui_Reload;
	IconLowGun ui_LowGun;
	vector<FullBullet*> ui_Full;

	int width;
	int height;

public:
	float ratioRemainBullet;
};

