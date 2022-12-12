#include "Player.h"

Player* Player::Instance = nullptr;
OBJ* Player::_Obj = nullptr;

Player::Player() : Mesh(this)
{
	name = "Player";

	// Mesh
	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Player/", "SpaceShip.obj");
	}
	obj = _Obj;

	// Tranform
	transform.local->scale *= 0.001;

	// Collider
	collider.tag = "Player";
	collider.SetBox_OBB(vec3(obj->vBlock.max - obj->vBlock.min));
	collider.object = this;

	// Object
	upgrade = new UpgradeControl(this);

	// Resource Init
	ironPool.InitPool(5, 1, 1.0f, &transform);
	mineralPool.InitPool(5, 1, 1.0f, &transform);

	// Equipment Init
	equipment["Harpoon"] = new Harpoon;
	equipment["LowGun"] = new LowGun;
	equipment["Guidance"] = new Guidance;
	
	for (auto& eq : equipment)
		eq.second->SetActive(false);
	equipment.find("Harpoon")->second->SetActive(true);
	
	Render::objectRender->AddObject(this);
}

Player::~Player()
{
}


void Player::Init()
{
	for (const auto& world : transform.world)
	{
		for (auto& eq : equipment)
			eq.second->transform.world.push_back(world);
	}

	for (auto& eq : equipment)
		eq.second->transform.world.push_back(transform.local);
}


void Player::Update()
{
	Handle_Event(key);
	Handle_Event(specialKey);
	Handle_Event_Up(keyUp);
	Handle_Event_Up(specialKeyUp);
}

void Player::Handle_Event(unsigned char key)
{
	float frameSpeed = speed * FrameTime::oneFrame;

	switch (key)
	{
	case 'w':
		move_front = true;
		break;
	case 's':
		move_back = true;
		break;
	case 'r':
		dynamic_cast<LowGun*>(equipment.find("LowGun")->second)->ReLoad();
		//if (equipment->GetType() == EqType::LOWGUN) {
		//	dynamic_cast<LowGun*>(equipment)->ReLoad();
		//	return;
		//};
		break;

	case 'e':
		upgrade->SetActive(!upgrade->ActiveSelf());
		break;
	}
}

void Player::Handle_Event(int specialKey)
{
	//Harpoon* _harpoon; LowGun* _lowgun;
	switch (specialKey)
	{
	//case GLUT_KEY_CTRL_L:
		//switch (equipment->GetType()) {
		//case EqType::HARPOON:
		//	if (equipment->GetState() == State::IDLE) {
		//		if (_harpoon = dynamic_cast<Harpoon*>(equipment))
		//			_harpoon->ChargingEnergy();
		//	}
		//	break;
		//case EqType::LOWGUN:
		//	if (_lowgun = dynamic_cast<LowGun*>(equipment)) {
		//		int firedBulletNum = _lowgun->Fire(transform);
		//		cout << "Fired Bulled Num : " << firedBulletNum << endl;
		//	}
		//	break;
		//}
	}
}

void Player::Handle_Event_Up(unsigned char key)
{
	switch (key)
	{
	case 'w':
		move_front = false;
		break;
	case 's':
		move_back = false;
		break;
	}
}

void Player::Handle_Event_Up(int specialKeyUp)
{
	switch (specialKeyUp)
	{
	case GLUT_KEY_CTRL_L:
		//if (equipment->GetType() == EqType::HARPOON)
		//{
		//	dynamic_cast<Harpoon*>(equipment)->FinishCharging();
		//}
		break;
	}
}

void Player::MyTimer()
{
	if (move_front) {
		transform.LookAt(-speed);
	}
	if (move_back) {
		transform.LookAt(speed);
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
				equipment.find("Guidance")->second->isDragged = false;
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
	transform.CurrentFront();
}