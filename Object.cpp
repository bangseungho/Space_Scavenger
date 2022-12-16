#include "Object.h"

vector<Object*> Object::initObject;
int Object::ID_Count = 0;
unsigned char Object::key;
unsigned char Object::keyUp;
int Object::specialKey;
int Object::specialKeyUp;

unsigned int Object::meterialBlockLoaction;

Object::Object(): transform()
{
	id = ID_Count++;
	name = "UnName";
	isActive = true;

	allObject.push_back(this);
	initObject.push_back(this);
}

Object::~Object()
{
	allObject.erase(remove(allObject.begin(), allObject.end(), this), allObject.end());
}

void Object::Update()
{
}
void Object::Init()
{
}

void Object::SetActive(bool value)
{
	if (this->isActive == false && value == true)
		this->Enable();
	else if (this->isActive == true && value == false)
		this->Disable();

	this->isActive = value;
}
void Object::Info()
{
	cout << id << " : " << name << endl;
}

void Object::MyTimer()
{
}

mat4& Object::SetMatrix()
{
	mat4 localModel = mat4(1.0);
	mat4 worldModel = mat4(1.0);

	for (auto& world : transform.world)
	{
		//worldModel = translate(worldModel, world->pivot);
		worldModel = translate(worldModel, world->position);
		worldModel = rotate(worldModel, radians(world->rotation.x), vec3(1.0, 0, 0));
		worldModel = rotate(worldModel, radians(world->rotation.y), vec3(0, 1.0, 0));
		worldModel = rotate(worldModel, radians(world->rotation.z), vec3(0, 0, 1.0));
		worldModel = scale(worldModel, world->scale);
	}

	localModel = translate(localModel, transform.local->pivot);
	localModel = translate(localModel, transform.local->position);
	localModel = rotate(localModel, radians(transform.local->rotation.x), vec3(1.0, 0, 0));
	localModel = rotate(localModel, radians(transform.local->rotation.y), vec3(0, 1.0, 0));
	localModel = rotate(localModel, radians(transform.local->rotation.z), vec3(0, 0, 1.0));
	localModel = scale(localModel, transform.local->scale);

	transform.localModel = localModel;
	transform.worldModel = worldModel;
	transform.model = worldModel * localModel;

	return transform.model;
}