#include "Player.h"

Player* Player::Instance = nullptr;
VertexBlock* Player::_Block = nullptr;

Player::Player() : Mesh(this),
ironPool(1,1,3.0f, &transform)
{
	name = "Player";

	if (_Block == nullptr)
	{
		_Block = new VertexBlock;
		ReadObj((char*)"SPACESHIP_1.obj", *_Block);
	}

	block = _Block;

	collider.SetBox_OBB(vec3(2));
	collider.object = this;
	Render::meshtRender->AddObject(this);
}

Player::~Player()
{
}

void Player::Init()
{
	collider.tag = "player";


	color.SetRandomColor();
	transform.worldScale *= 1;

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
	case 'a':
		transform.worldRotation.y += 90;
		transform.LookAt(speed);
		transform.worldRotation.y -= 90;
		break;
	case 'd':
		transform.worldRotation.y -= 90;
		transform.LookAt(speed);
		transform.worldRotation.y += 90;
		break;
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
	default:
		break;
	}
}

void Player::Collision()
{
	for (const auto& other : Collider::allCollider)
	{
		if (other->object->id == this->id)
			continue;
		if (!other->object->ActiveSelf())
			continue;
		if (!other->isCollide)
			continue;

		if (!collider.OBBCollision(collider, *other))
			continue;
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