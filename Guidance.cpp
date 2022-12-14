#include "Guidance.h"

OBJ* Guidance::_Obj = nullptr;

Guidance::Guidance()
{
	if(_Obj == nullptr)
	{	//임시
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Equipment/Guidance/" , "Guidance.obj");
	}
	obj = _Obj;

	serchDistnace = 10;

	// Transform
	transform.local->position = vec3(3);

	sound_Dragged.Load("Sound/Player/Dragged.mp3");

	Render::objectRender->AddObject(this);
}

Guidance::~Guidance()
{
}

void Guidance::Enable()
{
}

void Guidance::Disable()
{
	wave.SetActive(false);
}

void Guidance::Init()
{
	for (const auto& world : transform.world)
	{
		wave.transform.world.push_back(world);
	}
	wave.transform.world.push_back(transform.local);
}

void Guidance::Update()
{
	SerchResource();

	if (isDragged)
	{
		transform.RotateAtTarget(wave.resource->transform, 1);
		vec3 rotate = vec3(0);
		for (const auto& world : transform.world)
			rotate += world->rotation;
		transform.local->rotation -= rotate;
		//transform.local->rotation = -transform.local->rotation;
	}
}
void Guidance::SerchResource()
{
	if (isDragged)	//이미 선택한 자원이 있으면 리턴
		return;

	sound_Dragged.Stop();
	wave.SetActive(false);
	wave.resource = nullptr;

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
		wave.resource = reinterpret_cast<Resource*>(other->object);

		if (wave.resource)
		{
			wave.resource->OnDragged(&transform, 10);
			isDragged = true;
			sound_Dragged.RepeatPlay();
			wave.SetActive(true);
		}
		else
		{
			cout << name << " : Resource를 찾지 못했습니다." << endl;
			continue;
		}
		return;
	}
}
OBJ* Guidance::Wave::_Obj = nullptr;

Guidance::Wave::Wave() : Mesh(this)
{
	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Equipment/Guidance/", "Wave.obj");
	}
	obj = _Obj;

	resource = nullptr;

	transform.local->scale *= 0.9;
	color.A = 0.3f;
	SetActive(false);

	Render::objectRender->AddObject(this);
}

Guidance::Wave::~Wave()
{
}

void Guidance::Wave::Disable()
{
	transform.local->scale.y = 0;
}

void Guidance::Wave::Update()
{
	vec3 pos = (resource->transform.model - transform.model) * vec4(0, 0, 0, 1);
	float lenth = length(pos);
	pos = normalize(pos);
	if(lenth > transform.local->scale.y)
		transform.local->scale.y += FrameTime::oneFrame * lenth;
	else
		transform.local->scale.y -= FrameTime::oneFrame * lenth;
	transform.local->position.y = transform.local->scale.y;
}

mat4& Guidance::Wave::SetMatrix()
{
	mat4 localModel = mat4(1.0);
	mat4 worldModel = mat4(1.0);

	for (auto& world : transform.world)
	{
		worldModel = translate(worldModel, world->pivot);
		worldModel = translate(worldModel, world->position);
		worldModel = rotate(worldModel, radians(world->rotation.y), vec3(0, 1.0, 0));
		worldModel = rotate(worldModel, radians(world->rotation.x), vec3(1.0, 0, 0));
		worldModel = rotate(worldModel, radians(world->rotation.z), vec3(0, 0, 1.0));
		worldModel = scale(worldModel, world->scale);
	}

	localModel = translate(localModel, transform.local->pivot);
	localModel = translate(localModel, transform.local->position);
	localModel = rotate(localModel, radians(transform.local->rotation.y), vec3(0, 1.0, 0));
	localModel = rotate(localModel, radians(transform.local->rotation.x), vec3(1.0, 0, 0));
	localModel = rotate(localModel, radians(transform.local->rotation.z), vec3(0, 0, 1.0));
	localModel = scale(localModel, transform.local->scale);

	transform.localModel = localModel;
	transform.worldModel = worldModel;
	transform.model = worldModel * localModel;

	return transform.model;
}