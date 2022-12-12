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

	collider.tag = "Resource";
	collider.object = this;
	transform.local->scale *= 0.01;

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
}

void Resource::Disable()
{
	isDragged = false;
}

void Resource::Init()
{
	
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

		if (other->tag == "Player" && level == 1)
		{
			SetActive(false);
		}

		if (other->tag == "Bullet")
		{
			other->object->SetActive(false);
			if (level > 1) {
				level -= 1;
			}
			cout << level << endl;
		}
	}
}


void Resource::OnDragged(Transform* _Target, float _Speed)
{
	isDragged = true;
	target = _Target;
	draggedSpeed = _Speed;
}

//Target¿¡ ²ø·Á°¨
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
