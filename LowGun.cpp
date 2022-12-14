#include "LowGun.h"

OBJ* LowGun::_Obj = nullptr;

LowGun::LowGun()
{
	SetType(EqType::LOWGUN);
	name = "Lowgun";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Equipment/", "Gun.obj");
	}

	fireSound.Load("Sound/fire_bullet.mp3", false);
	loadSound.Load("Sound/load_bullet.mp3", false);

	obj = _Obj;

	transform.local->scale = vec3(200);
	transform.local->rotation.y = -90;
	transform.local->position.y = 600;
	bulletNum = 10;

	for (int i = 0; i < bulletNum; ++i) {
		bullets.push_back(new Bullet);
	}

	Render::objectRender->AddObject(this, "Lowgun");
}

LowGun::~LowGun()
{
	
}

void LowGun::Update()
{
}

int LowGun::Fire(const Transform& transform)
{
	if (fireCount < bulletNum) {
		fireSound.Play();
		bullets[fireCount]->SetActive(true);
		bullets[fireCount]->transform.local->position = transform.local->position;
		bullets[fireCount]->trajectory = transform.front;
		bullets[fireCount]->transform.local->position.y += 0.6;
		bullets[fireCount]->gunPos = transform.local->position;
		fireCount++;
	}
	return fireCount;
}

void LowGun::ReLoad()
{
	loadSound.Play();
	fireCount = 0;
}

