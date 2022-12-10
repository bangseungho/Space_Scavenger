#include "LowGun.h"

OBJ* LowGun::_Obj = nullptr;

LowGun::LowGun()
{
	SetType(EqType::LOWGUN);
	name = "Lowgun";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj((char*)"Sphere.obj");
	}

	fireSound.Load("Sound/fire_bullet.mp3", false);
	loadSound.Load("Sound/load_bullet.mp3", false);

	transform.local->scale = vec3(0.1);
	transform.local->position.y += 3;
	obj = _Obj;
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

