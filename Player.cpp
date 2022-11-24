#include "Player.h"

Player* Player::Instance = nullptr;

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	Cube::Init();
	collider.tag = "player";

	transform.worldScale *= 0.2;
}


void Player::Update()
{
	Cube::Update();

	Handle_Evnet(key);
	Handle_Evnet(specialKey);
}

void Player::Handle_Evnet(unsigned char key)
{
	float frameSpeed = speed * FrameTime::oneFrame;
	float x = transform.worldRotation.x;
	transform.worldRotation.x -= x;
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
	}
	transform.worldRotation.x += x;
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

		cout << "Ãæµ¹ : " << other->tag << endl;
	}
}
