#include "Equipment.h"

VertexBlock* Equipment::_Block = nullptr;

Equipment::Equipment() : Mesh(this)
{
	name = "Harpoon";

	if (_Block == nullptr)
	{
		_Block = new VertexBlock;
		ReadObj((char*)"Harpoon.obj", *_Block);
	}

	block = _Block;

	collider.tag = "Harpoon";
	collider.SetBox_OBB(block->max - block->min);
	collider.object = this;

	Render::meshtRender->AddObject(this, "Harpoon");
}

void Equipment::Init()
{
	color.SetRandomColor();
	transform.worldScale *= 0.5;
}

Equipment::~Equipment()
{
}

void Equipment::Update()
{
	Handle_Evnet(key);
	Handle_Evnet(specialKey);
}

void Equipment::FireSet()
{
	cout << "Fire_Harpoon!!" << endl;
	firing = true;
	charging = true;
	strength = 0;
	Fire();
}

void Equipment::Handle_Evnet(int specialKey)
{
	switch (specialKey)
	{

	}
}


void Equipment::Fire()
{
	float frameSpeed = speed * FrameTime::oneFrame;

	if (firing) {
		if (strength < max_strength)
		{
			transform.localPosition.z -= frameSpeed * max_strength / 30.0;
			transform.worldScale.z += frameSpeed * max_strength / 30.0;
		}
		else if (strength < max_strength * 2) {
			transform.localPosition.z += frameSpeed * max_strength / 30.0;
			transform.worldScale.z -= frameSpeed * max_strength / 30.0;
		}
		else {
			transform.localPosition.z = 0;
			transform.worldScale.z = 0.5;
			firing = false;
			max_strength = 0;
		}
		strength++;
	}
}
