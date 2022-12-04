#include "Guidance.h"

Guidance::Guidance()
{
	myType = EqType::GUIDANCE;

	collider.SetBox_OBB(vec3(2));
	collider.object = this;
	collider.tag = "Guidance";

	serchDistnace = 100;
}

Guidance::~Guidance()
{
}

void Guidance::Update()
{
	SerchResource();
}

void Guidance::OnCollision()
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

		//if (other->tag == "Resource")
		//{
		//	if (resourceType.find(other->object->name) != resourceType.end())
		//	{
		//		collider.isCollide = false;
		//		return;
		//	}
		//}
	}
}

void Guidance::SerchResource()
{
	vec3 myPos = transform.model * vec4(0, 0, 0, 1);
	for (auto& other : Collider::allCollider)
	{
		if (!other->object->ActiveSelf())
			continue;
		if (!other->isCollide)
			continue;
		if (other->object->id == id)
			continue;

		if (other->tag != "Resource")
			continue;

		vec3 targetPos = other->object->transform.model * vec4(0, 0, 0, 1);
		float dis = length(myPos - targetPos);

		if (dis > serchDistnace)
			continue;

		Resource* resource = reinterpret_cast<Resource*>(other->object);

		if (resource)
		{
			collider.isCollide = false;
			resource->OnDragged(&transform);
		}
		else
		{
			cout << name << " : Resource를 찾지 못했습니다." << endl;
			continue;
		}
		return;
	}
}
