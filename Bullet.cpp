#include "Bullet.h"
#include "Player.h"

OBJ* Bullet::_Obj = nullptr;

Bullet::Bullet()
{
	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Equipment/LowGun/", "Bullet.obj");
	}
	obj = _Obj;

	SetType(EqType::BULLET);
	name = "Bullet";

	collider.tag = "Bullet";
	collider.object = this;
	speed = 100;
	isUse = false;

	transform.local->rotation.x = -90;
	collider.SetBox_OBB(vec3(2));

	Render::objectRender->AddObject(this, "Bullet");
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	float BulletSpeed = speed * FrameTime::oneFrame * 60;
	transform.local->position -= trajectory;
}

void Bullet::OnCollision()
{
	for (auto& other : Collider::allCollider)
	{
		if (!other->isCollide)
			continue;

		if (other->tag != "Resource")
			continue;

		if (!other->OBBCollision(collider, *other))
			continue;

		if (other->tag == "Resource")
		{
			// Bullet이 Resouce에 맞으면 Resouce에서 삭제
		}
	}
}
