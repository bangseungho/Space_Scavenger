#include "Guidance.h"

Guidance::Guidance()
{
	SetType(EqType::GUIDANCE);
	{	//임시
		obj = new OBJ;
		obj->ReadObj("Obj/Default/" , "Cube.obj");
		isDraw = false;
	}

	serchDistnace = 10;

	sound_Dragged.Load("Sound/Player/Dragged.mp3");
}

Guidance::~Guidance()
{
}

void Guidance::Update()
{
	SerchResource();
}

void Guidance::SerchResource()
{
	if (isDragged)	//이미 선택한 자원이 있으면 리턴
		return;

	sound_Dragged.Stop();

	vec3 myPos = transform.model * vec4(0, 0, 0, 1);
	for (auto& other : Collider::allCollider)
	{
		if (!other->object->ActiveSelf())
			continue;
		if (!other->isCollide)
			continue;

		if (other->tag != "Resource")
			continue;

		// 자원과 장비 사이의 거리 측정
		vec3 targetPos = other->object->transform.model * vec4(0, 0, 0, 1);
		float dis = length(myPos - targetPos);

		if (dis > serchDistnace)
			continue;

		// 찾은 자원의 함수를 사용하기 위해 형변환
		Resource* resource = reinterpret_cast<Resource*>(other->object);

		if (resource)
		{
			resource->OnDragged(&transform, 10);
			isDragged = true;
			sound_Dragged.RepeatPlay();
		}
		else
		{
			cout << name << " : Resource를 찾지 못했습니다." << endl;
			continue;
		}
		return;
	}
}
