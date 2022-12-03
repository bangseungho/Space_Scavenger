#include "Player.h"

Player* Player::Instance = nullptr;
VertexBlock* Player::_Block = nullptr;

Player::Player() : Mesh(this)
{
	name = "Player";

	if (_Block == nullptr)
	{
		_Block = new VertexBlock;
		ReadObj((char*)"SPACESHIP_1.obj", *_Block);
	}

	block = _Block;
	ironPool.InitPool(5, 1, 1.0f, &transform);
	equipment = new Harpoon();
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

	equipment.targetPos = &transform;
}


void Player::Update()
{
	Handle_Evnet(key);
	Handle_Evnet(specialKey);
}

void Player::Handle_Evnet(unsigned char key)
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

void Player::Handle_Evnet(int specialKey)
{
	switch (specialKey)
	{
	case GLUT_KEY_CTRL_L:
		if (equipment->GetType() == EqType::HARPOON)
		{

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
			cout << "충돌 " << endl;
			cout << other->tag << endl;
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
