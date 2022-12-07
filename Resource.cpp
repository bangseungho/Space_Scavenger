#include "Resource.h"

libxl::Book* Resource::book = nullptr;
libxl::Sheet* Resource::sheet = nullptr;

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

	amount = 0;
	velocity = vec3(0);
	
	draggedSpeed = 1;
	isDragged = false;
	Render::meshtRender->AddObject(this, "Resource");
}

Resource::~Resource()
{
	amount = RandomInt(1, 5);
}

void Resource::Enable()
{
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
