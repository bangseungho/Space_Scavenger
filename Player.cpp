#include "Player.h"

Player* Player::Instance = nullptr;
OBJ* Player::_Obj = nullptr;

Player::Player() : Mesh(this)
{
	name = "Player";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Player/", "SpaceShip.obj");
	}

	obj = _Obj;
	ironPool.InitPool(5, 1, 1.0f, &transform);
	//equipment = new Harpoon;
	equipment = new LowGun;
	//equipment = new Guidance;
	Render::meshtRender->AddObject(this);
}

Player::~Player()
{
}

void Player::Init()
{
	collider.tag = "Player";
	collider.SetBox_OBB(vec3(2));
	collider.object = this;
}


void Player::Update()
{
	Handle_Event(key);
	Handle_Event(specialKey);
	Handle_Event_Up(specialKeyUp);
}

void Player::Handle_Event(unsigned char key)
{
	float frameSpeed = speed * FrameTime::oneFrame;
	switch (key)
	{
	case 'w':
		transform.LookAt(speed);
		break;
	case 's':
		transform.LookAt(-speed);
		break;
	case 'q':
		transform.worldRotation.y++;
		break;
	case 'e':
		transform.worldRotation.y--;
		break;
	}

}

void Player::Handle_Event(int specialKey)
{
	switch (specialKey)
	{
	case GLUT_KEY_CTRL_L:
		switch (equipment->GetType()) {
		case EqType::HARPOON:
			if (equipment->GetState() == State::IDLE) {
				equipment->ChargingEnergy();
			}
			break;
		case EqType::LOWGUN:
			equipment->Fire();
			break;
		}
	}
}

void Player::Handle_Event_Up(int specialKeyUp)
{
	switch (specialKeyUp)
	{
	case GLUT_KEY_CTRL_L:
		if (equipment->GetType() == EqType::HARPOON)
		{
			equipment->FinishCharging();
		}
		break;
	}
}

void Player::OnCollision()
{
	for (auto& other : Collider::allCollider)
	{
		if (!other->object->ActiveSelf())
			continue;
		if (!other->isCollide)
			continue;
		if (other->object->id == id)
			continue;
		
		if (!other->OBBCollision(collider, *other))
			continue;

		if (other->tag == "Resource")
		{
			Resource* resource = reinterpret_cast<Resource*>(other->object);
			if (resource->isDragged)
				equipment->isDragged = false;
		}
	}
}

mat4& Player::SetMatrix()
{
	mat4 worldModel = mat4(1.0);
	mat4 localModel = mat4(1.0);

	localModel = translate(localModel, transform.localPivot);
	localModel = translate(localModel, transform.localPosition);
	localModel = rotate(localModel, radians(transform.localRotation.y), vec3(0, 1.0, 0));	// y축으로 자전 해주고 싶어 처음에 추가
	localModel = rotate(localModel, radians(transform.localRotation.x), vec3(1.0, 0, 0));
	localModel = rotate(localModel, radians(transform.localRotation.z), vec3(0, 0, 1.0));
	localModel = scale(localModel, transform.localScale);

	worldModel = translate(worldModel, transform.worldPivot);
	worldModel = translate(worldModel, transform.worldPosition);
	worldModel = rotate(worldModel, radians(transform.worldRotation.y), vec3(0, 1.0, 0));
	worldModel = rotate(worldModel, radians(transform.worldRotation.x), vec3(1.0, 0, 0));
	worldModel = rotate(worldModel, radians(transform.worldRotation.z), vec3(0, 0, 1.0));
	worldModel = scale(worldModel, transform.worldScale);

	transform.model = localModel * worldModel;

	equipment->transform = transform;
	equipment->transform.worldPosition.y += 2;

	return transform.model;
}

void Player::QuestHandle()
{
}

void Player::FaceMove(const vec2& diffPos)
{
	vec2 speed = vec2(3, 2);
	vec2 fMoveSpeed = diffPos * FrameTime::oneFrame * speed;
	transform.worldRotation.y -= fMoveSpeed.x;
	transform.worldRotation.x += fMoveSpeed.y;
}