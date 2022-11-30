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

	collider.SetBox_OBB(block->max -block->min);
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

//void Player::MouseWheelEvent(int wheel, int direction, vec2 pos)
//{
//	vec2 diffPos = (pos - MouseControl::clickPos) * FrameTime::oneFrame * vec2(10);
//	transform.worldRotation.y -= diffPos.x;
//	transform.worldRotation.x -= diffPos.y;
//}