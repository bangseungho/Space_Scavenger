#include "Equipment.h"

Equipment::Equipment() : Mesh(this)
{
	SetState(State::IDLE);

	isDragged = false;
	isUnLock = false;
}

Equipment::~Equipment()
{
}

void Equipment::SetType(EqType type)
{
	myType = type;
}

EqType Equipment::GetType()
{
	return this->myType;
}

void Equipment::SetState(State state)
{
	myState = state;
}

State Equipment::GetState()
{
	return myState;
}

void Equipment::Init()
{
}

void Equipment::Update()
{
	
}

void Equipment::Handle_Evnet(int specialKey)
{
}

mat4& Equipment::SetMatrix()
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
