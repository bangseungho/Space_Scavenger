#include "Player.h"

Player* Player::Instance = nullptr;
OBJ* Player::_Obj = nullptr;

Player::Player() : Mesh(this)
{
	name = "Player";

	// Mesh 초기화
	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Player/", "SpaceShip.obj");
	}
	obj = _Obj;

	// Collider 초기화
	collider.tag = "Player";
	collider.SetBox_OBB(vec3(2));
	collider.object = this;

	// Object 초기화
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
	// Object들의 Transform 초기화
	for (const auto& world : transform.world)
	{
		equipment->transform.world.push_back(world);
	}

	equipment->transform.world.push_back(transform.local);
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
		transform.LookAt(-speed);
		break;
	case 's':
		transform.LookAt(speed);
		break;
	case 'q':
		transform.local->rotation.y++;
		break;
	case 'e':
		transform.local->rotation.y--;
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
	mat4 localModel = mat4(1.0);
	mat4 worldModel = mat4(1.0);

	for (auto& world : transform.world)
	{
		worldModel = translate(worldModel, world->pivot);
		worldModel = translate(worldModel, world->position);
		worldModel = rotate(worldModel, radians(world->rotation.y), vec3(0, 1.0, 0));
		worldModel = rotate(worldModel, radians(world->rotation.x), vec3(1.0, 0, 0));
		worldModel = rotate(worldModel, radians(world->rotation.z), vec3(0, 0, 1.0));
		worldModel = scale(worldModel, world->scale);
	}

	localModel = translate(localModel, transform.local->pivot);
	localModel = translate(localModel, transform.local->position);
	localModel = rotate(localModel, radians(transform.local->rotation.y), vec3(0, 1.0, 0));
	localModel = rotate(localModel, radians(transform.local->rotation.x), vec3(1.0, 0, 0));
	localModel = rotate(localModel, radians(transform.local->rotation.z), vec3(0, 0, 1.0));
	localModel = scale(localModel, transform.local->scale);

	transform.localModel = localModel;
	transform.worldModel = worldModel;
	transform.model = worldModel * localModel;

	return transform.model;
}

void Player::QuestHandle()
{
}

void Player::FaceMove(const vec2& diffPos)
{
	vec2 speed = vec2(15, 10);
	vec2 fMoveSpeed = diffPos * FrameTime::oneFrame * speed;
	transform.local->rotation.y -= fMoveSpeed.x;
	transform.local->rotation.x -= fMoveSpeed.y;
}