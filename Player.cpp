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
	//equipment = new Harpoon();
	equipment = new Guidance;
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
		transform.localRotation.y++;
		break;
	case 'e':
		transform.localRotation.y--;
		break;
	}
}

void Player::Handle_Event(int specialKey)
{
	switch (specialKey)
	{
	case GLUT_KEY_CTRL_L:
		if (equipment->GetType() == EqType::HARPOON && 
			equipment->GetState() == State::IDLE)
		{
			equipment->ChargingEnergy();
		}
		break;
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
	mat4 lModel = mat4(1.0);

	lModel = translate(lModel, transform.localPivot);
	lModel = translate(lModel, transform.localPosition);
	lModel = rotate(lModel, radians(transform.localRotation.x), vec3(1.0, 0, 0));
	lModel = rotate(lModel, radians(transform.localRotation.y), vec3(0, 1.0, 0));
	lModel = rotate(lModel, radians(transform.localRotation.z), vec3(0, 0, 1.0));
	lModel = scale(lModel, transform.localScale);

	*transform.localModel = lModel;
	*transform.model = (*transform.worldModel) * (lModel);

	return *transform.model;
}

void Player::QuestHandle()
{
}

void Player::FaceMove(const vec2& diffPos)
{
	vec2 speed = vec2(3, 2);
	vec2 fMoveSpeed = diffPos * FrameTime::oneFrame * speed;
	transform.localRotation.y -= fMoveSpeed.x;
	transform.localRotation.x += fMoveSpeed.y;
}