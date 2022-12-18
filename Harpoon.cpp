#include "Harpoon.h"

OBJ* Harpoon::_Obj = nullptr;

Harpoon::Harpoon()
{
	SetType(EqType::HARPOON);
	name = "Harpoon";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Equipment/Harpoon/", "Harpoon.obj");
	}

	obj = _Obj;

	collider.tag = "Harpoon";
	collider.SetBox_OBB(vec3(2));
	collider.object = this;

	transform.local->position.z += 5;
	transform.local->position.y -= 3;

	gauge = new Gauge();

	Render::objectRender->AddObject(this, "Harpoon");
}

Harpoon::~Harpoon()
{
}

void Harpoon::Init()
{
	curEnergy = 0;
	chargedEnergy = 0;
	speed = 100;
	color.A = 1.0;
}

void Harpoon::Update()
{
	Handle_Event();
	Handle_Event_Up();
}

void Harpoon::ChargingEnergy()
{
	startTime = clock();

	curEnergy = 0;
	chargedEnergy = 0;

	SetState(State::CHARGING);
}

void Harpoon::FinishCharging()
{
	chargedEnergy = chargingTime * 10;

	SetState(State::FIRING);
}

void Harpoon::MyTimer()
{
	endTime = clock();
	chargingTime = (endTime - startTime) / CLOCKS_PER_SEC;
	if (chargingTime > maxEnergy) chargingTime = maxEnergy;

	switch (GetState()) {
	case State::IDLE:
		gauge->transform.local->scale.x = 0;
		break;
	case State::CHARGING:
		gauge->transform.local->scale.x = chargingTime;
		break;
	case State::FIRING:
		Fire();
		break;
	}
}

void Harpoon::Fire()
{
	float frameSpeed = speed * FrameTime::oneFrame;

	if (curEnergy < chargedEnergy)
	{
		transform.local->position.z += frameSpeed * chargedEnergy / 15.0;
		transform.local->scale.z += frameSpeed * chargedEnergy / 30.0;
	}
	else {
		transform.local->position.z -= frameSpeed * chargedEnergy / 75.0;
		transform.local->scale.z -= frameSpeed * chargedEnergy / 150.0;

		if (transform.local->scale.z < 0.005) {
			transform.local->position.z = 5;
			transform.local->scale.z = 1;
			chargedEnergy = 0;
			SetState(State::IDLE);
		}
	}
	curEnergy++;
}

void Harpoon::OnCollision()
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
		}
	}
}

void Harpoon::Handle_Event()
{
	switch (specialKey)
	{
	case GLUT_KEY_CTRL_L:
		ChargingEnergy();
		break;
	}
}

void Harpoon::Handle_Event_Up()
{
	switch (specialKeyUp)
	{
	case GLUT_KEY_CTRL_L:
		FinishCharging();
		break;
	}
}
