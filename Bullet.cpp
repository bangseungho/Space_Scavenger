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

void Bullet::OnCollision()
{
	//for (auto& other : Collider::allCollider)
	//{
	//	if (!other->isCollide)
	//		continue;

	//	if (other->tag != "Resource")
	//		continue;

	//	cout << "RESOURCE COLLIDER" << endl;
	//}
}
