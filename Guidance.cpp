#include "Guidance.h"

Guidance::Guidance()
{
	SetType(EqType::GUIDANCE);
	{	//�ӽ�
		obj = new OBJ;
		obj->ReadObj((char*)"Cube.obj");
		isDraw = false;
	}

	serchDistnace = 1000;
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
		}
		else
		{
			cout << name << " : Resource�� ã�� ���߽��ϴ�." << endl;
			continue;
		}
		return;
	}
}
