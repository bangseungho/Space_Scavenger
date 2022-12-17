#include "LowGun.h"

OBJ* LowGun::_Obj = nullptr;

LowGun::LowGun()
{
	SetType(EqType::LOWGUN);
	name = "Lowgun";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Equipment/LowGun/", "Gun.obj");
	}
	obj = _Obj;

	fireSound.Load("Sound/fire_bullet.mp3", false);
	loadSound.Load("Sound/load_bullet.mp3", false);

	transform.local->rotation.y = -90;
	transform.local->position.y = 3;

	bulletNum = remainBullet = 12; // 총알 개수 12의 배수로 설정 업그레이드 또한 12..24..36

	ui_bulletNum = new BulletNum();

	for (int i = 0; i < bulletNum; ++i) {
		bullets.push_back(new Bullet);
	}

	Render::objectRender->AddObject(this, "Lowgun");
}

LowGun::~LowGun()
{
	
}

void LowGun::Enable() {
	ui_bulletNum->SetActive(true);
}

void LowGun::Disable() {
	ui_bulletNum->SetActive(false);
}

void LowGun::Update()
{
	remainBullet = bulletNum - fireCount;
	ui_bulletNum->GetBulletInfo(bulletNum, remainBullet);
}

int LowGun::Fire(const Transform& transform)
{
	if (fireCount < bulletNum) {
		fireSound.Play();
		bullets[fireCount]->SetActive(true);
		bullets[fireCount]->transform.local->rotation = transform.local->rotation;
		bullets[fireCount]->transform.local->position = transform.local->position;
		bullets[fireCount]->transform.local->rotation.x += 90;
		bullets[fireCount]->trajectory = transform.front;

		fireCount++;
	}
	return fireCount;
}

void LowGun::ReLoad()
{
	loadSound.Play();
	fireCount = 0;
}

