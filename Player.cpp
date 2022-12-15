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

	// Speed
	speedBlock.current = 10;
	speedBlock.max = 100;
	speedBlock.accelerat = 1;

	// Tranform

	// Collider
	collider.tag = "Player";
	collider.SetBox_OBB(vec3(obj->vBlock.max - obj->vBlock.min));
	collider.object = this;

	// Resource Init
	//ironPool.InitPool(5, 1, 1.0f, &transform);
	goldPool.InitPool(5, 1, 1.0f, &transform);
	mineralPool.InitPool(5, 1, 1.0f, &transform);
	emeraldlPool.InitPool(5, 1, 1.0f, &transform);
	uraniumPool.InitPool(5, 1, 1.0f, &transform);

	// Equipment Init
	equipment["Harpoon"] = new Harpoon;
	equipment["LowGun"] = new LowGun;
	Guidance* guidance = new Guidance;
	equipment["Guidance"] = guidance;
	
	for (auto& eq : equipment)
		eq.second->SetActive(false);
	equipment.find("LowGun")->second->SetActive(true);
	
	// Object
	upgrade = new UpgradeControl(this);
	questControl = new QuestControl(this);
	guidanceControl = new GuidanceControl(guidance);

	hp = 100;

	// Data Setting
	GetDate();
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
	float frameSpeed = speedBlock.current * FrameTime::oneFrame;
	LowGun* lowGun;

	switch (key)
	{
	case 'w':
		move_front = true;
		break;
	case 's':
		move_back = true;
		break;
	case 'r':
		lowGun = reinterpret_cast<LowGun*>(equipment.find("LowGun")->second);
		if (!lowGun)
			return;
		lowGun->ReLoad();
		break;
	case 'q':
		questControl->SetActive(!questControl->ActiveSelf());
		upgrade->SetActive(false);
		guidanceControl->SetActive(false);
		break;
	case 'e':
		questControl->SetActive(false);
		upgrade->SetActive(!upgrade->ActiveSelf());
		guidanceControl->SetActive(false);
		break;
	case 'g':
		questControl->SetActive(false);
		upgrade->SetActive(false);
		guidanceControl->SetActive(!guidanceControl->ActiveSelf());
		break;
	}
}

void Player::Handle_Event(int specialKey)
{
	//Harpoon* _harpoon; LowGun* _lowgun;
	switch (specialKey)
	{
	case GLUT_KEY_CTRL_L:
		Harpoon* harpoon = reinterpret_cast<Harpoon*>(equipment.find("Harpoon")->second);
		LowGun* lowGun = reinterpret_cast<LowGun*>(equipment.find("LowGun")->second);
		Guidance* guidance = reinterpret_cast<Guidance*>(equipment.find("Guidance")->second);

		if (harpoon->ActiveSelf())
		{
			harpoon->ChargingEnergy();
		}

		if (lowGun->ActiveSelf())
		{
			lowGun->Fire(transform);
		}
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
		Harpoon* harpoon = reinterpret_cast<Harpoon*>(equipment.find("Harpoon")->second);
		harpoon->FinishCharging();
		break;
	}
}

void Player::MyTimer()
{
	if (move_front) {
		speedBlock.current += speedBlock.accelerat * FrameTime::oneFrame;
		if (speedBlock.current > speedBlock.max)
			speedBlock.current = speedBlock.max;
	}
	else if (move_back) {
		speedBlock.current -= speedBlock.accelerat* FrameTime::oneFrame;
		if (speedBlock.current < 0)
			speedBlock.current = 0;
	}
	transform.LookAt(speedBlock.current);
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

		Resource* resource = reinterpret_cast<Resource*>(other->object);
		if (resource->isDragged)
			equipment.find("Guidance")->second->isDragged = false;

		hp -= resource->level;
		resourceCount[resource->name] += resource->amount;

		if (resource->level > 0)
			speedBlock.current *= 0.7;
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

void Player::FaceMove(const vec2& diffPos)
{
	vec2 speed = vec2(15, 10);
	vec2 fMoveSpeed = diffPos * FrameTime::oneFrame * speed;
	transform.local->rotation.y -= fMoveSpeed.x;
	transform.local->rotation.x -= fMoveSpeed.y;
	transform.CurrentFront();
}

void Player::GetDate()
{
	PlayerData* data = PlayerData::Instance;
	int count = data->sheet->readNum(1, 0);
	for (int i = 0; i < count; i++)
	{
		wstring rName = data->sheet->readStr(i + 5, 2);
		string type;
		static std::locale loc("");
		auto& facet = use_facet<codecvt<wchar_t, char, mbstate_t>>(loc);
		type = wstring_convert<remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(rName);

		resourceCount[type] = data->sheet->readNum(i + 5, 3);
	}
}