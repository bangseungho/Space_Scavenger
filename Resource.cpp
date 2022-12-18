#include "Resource.h"

libxl::Book* Resource::book = nullptr;
libxl::Sheet* Resource::sheet = nullptr;

string Resource::filePath = "Obj/Resource/";

Resource::Resource() : Mesh(this)
{
	if (book == nullptr)
	{
		book = xlCreateXMLBook();
		book->load(L"Data/PlayerData.xlsx");
		sheet = book->getSheet(0);
	}
	SetActive(false);

	// Member 변수
	collider.tag = "Resource";
	collider.object = this;

	amount = RandomInt(1, 3);
	velocity = vec3(RandomFloat(-1,1), RandomFloat(-1, 1), RandomFloat(-1, 1));
	velocity = normalize(velocity);
	
	draggedSpeed = 1;
	isDragged = false;

	Render::objectRender->AddObject(this, "Resource");
}

Resource::~Resource()
{
	amount = RandomInt(1, 5);
}

void Resource::Enable()
{
	amount = RandomInt(1,3);
	velocity = vec3(RandomFloat(-1, 1), RandomFloat(-1, 1), RandomFloat(-1, 1));
	velocity = normalize(velocity);
	level = RandomInt(1, 7);
	transform.local->scale = vec3((float)level * 1.3f);
	color.SetColor({ 1,1,1,1 });
}

void Resource::Disable()
{
	isDragged = false;
}

void Resource::Init()
{
	collider.SetBox_OBB(vec3(obj->vBlock.max - obj->vBlock.min));
}

void Resource::Update()
{
	MoveMent();
	Dragged();
}

void Resource::OnCollision()
{
	for (auto& other : Collider::allCollider)
	{
		if (!other->object->ActiveSelf())
			continue;
		if (!other->isCollide)
			continue;
		if (other->object->id == id)
			continue;

		if (!Collider::OBBCollision(collider, *other))
			continue;

		if (other->tag == "Player")
		{
			SetActive(false);
		}

		if (other->tag == "Harpoon")
		{
			if (level > 1)
				level = 0;
		}

		if (other->tag == "Bullet")
		{
			if (level < 1)
			{
				color.R = 1;
				continue;
			}
			level -= 1;

			float hitColorValue = level * 0.1f;
			color.SetColor({ hitColorValue ,hitColorValue,hitColorValue, 1 });
		}
	}
}


void Resource::OnDragged(Transform* _Target, float _Speed)
{
	isDragged = true;
	target = _Target;
	draggedSpeed = _Speed;
	level = 0;
}

//Target에 끌려감
void Resource::Dragged()
{
	if (!isDragged)
		return;

	transform.LookAtTarget(*target, draggedSpeed);
}

void Resource::MoveMent()
{
	if (isDragged)
		return;

	vec3 speed = velocity * FrameTime::oneFrame;
	transform.local->position += speed * vec3(0.2);
	transform.local->rotation += speed * vec3(10);
}
