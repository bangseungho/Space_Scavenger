#include "Bullet.h"
#include "Player.h"

OBJ* Bullet::_Obj = nullptr;

Bullet::Bullet()
{
	SetType(EqType::BULLET);
	name = "Bullet";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj((char*)"Cube.obj");
	}

	obj = _Obj;
	transform.worldScale = vec3(0.1);
	collider.tag = "Bullet";
	collider.SetBox_OBB(vec3(2));
	collider.object = this;

	Render::meshtRender->AddObject(this, "Bullet");
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	speed = 200;
	float BulletSpeed = speed * FrameTime::oneFrame * 60;
	transform.LookAt(BulletSpeed);
}
