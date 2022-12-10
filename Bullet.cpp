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
		_Obj->ReadObj((char*)"Sphere.obj");
	}

	collider.tag = "Bullet";
	collider.object = this;

	speed = 200;
	isUse = false;

	obj = _Obj;
	transform.local->scale = vec3(0.1);
	collider.SetBox_OBB(vec3(2));

	Render::meshtRender->AddObject(this, "Bullet");
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
			// Bullet�� Resouce�� ������ Resouce���� ����
		}
	}
}
