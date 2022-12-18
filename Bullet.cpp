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
		_Obj->ReadObj("Obj/Equipment/LowGun/", "Bullet.obj");
	}
	obj = _Obj;

	collider.tag = "Bullet";
	collider.object = this;
	collider.SetBox_OBB(vec3(2));

	particle = new ParticleGenerator(10);

	transform.local->scale = vec3(1);
	speed = 1;

	SetActive(false);
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
		if (!other->object->ActiveSelf()) continue;
		if (!other->isCollide) continue;
		if (other->tag != "Resource") continue;
		if (!other->OBBCollision(collider, *other))	continue;

		if (other->tag == "Resource")
		{
			SetActive(false);
			particle->ExplodeParticles(transform);
		}
	}
}
