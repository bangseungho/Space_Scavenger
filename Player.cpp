#include "Player.h"

Player* Player::Instance = nullptr;
ObjectBlock* Player::_Block = nullptr;

Player::Player()
{
	name = "Player";

	if (_Block == nullptr)
	{
		_Block = new ObjectBlock;
		ReadObj((char*)"Player.obj", *_Block);
	}

	block.vertices = _Block->vertices;
	block.vertices_uvs = _Block->vertices_uvs;
	block.vertices_normals = _Block->vertices_normals;

	block.vertexIndices = _Block->vertexIndices;
	block.uvIndices = _Block->uvIndices;
	block.normalIndices = _Block->normalIndices;

	block.max = _Block->max;

	collider.SetBox_OBB(block.max);
	collider.object = this;
}

Player::~Player()
{
}

void Player::Init()
{
	Object::Init();
	collider.tag = "player";

	transform.worldScale *= 0.01;
	Render::objectRender->AddObject(this);
}


void Player::Update()
{
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
	case 'q':
		transform.worldRotation.y++;
		break;
	case 'e':
		transform.worldRotation.y--;
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
	}
}
