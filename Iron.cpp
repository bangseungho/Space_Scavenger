#include "Iron.h"

VertexBlock* Iron::_Block = nullptr;
int Iron::amountData = -1;

Iron::Iron()
{
	name = "Iron";

	if (_Block == nullptr)
	{
		_Block = new VertexBlock;
		ReadObj((char*)"Cube.obj", *_Block);	// 이름 변경 필수
	}

	block = _Block;

	collider.SetBox_OBB(vec3(2));

}

Iron::~Iron()
{
}

void Iron::Init()
{
	Resource::Init();

	if (amountData == -1)
	{
		amountData = sheet->readNum(1, 1);
	}
}

void Iron::OnCollision()
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

		if (other->tag == "Player")
		{
			SetActive(false);
			amountData++;

			// 임시
			sheet->writeNum(1, 1, amountData);
			book->errorMessage();
			book->save(L"Data/PlayerData.xlsx");
		}
	}
}
