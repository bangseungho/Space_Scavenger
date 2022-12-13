#include "Guidance.h"

Guidance::Guidance()
{
	SetType(EqType::GUIDANCE);
	{	//�ӽ�
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
	if (isDragged)	//�̹� ������ �ڿ��� ������ ����
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

		// �ڿ��� ��� ������ �Ÿ� ����
		vec3 targetPos = other->object->transform.model * vec4(0, 0, 0, 1);
		float dis = length(myPos - targetPos);

		if (dis > serchDistnace)
			continue;

		// ã�� �ڿ��� �Լ��� ����ϱ� ���� ����ȯ
		Resource* resource = reinterpret_cast<Resource*>(other->object);

		if (resource)
		{
			resource->OnDragged(&transform, 10);
			isDragged = true;
			sound_Dragged.RepeatPlay();
		}
		else
		{
			cout << name << " : Resource�� ã�� ���߽��ϴ�." << endl;
			continue;
		}
		return;
	}
}
