#include "Object.h"

//list<Object*> Object::allObject;	//main.cpp 에서 전역변수로 Object 호출시 static 부분 무시함 (이유는 모름)
int Object::ID_Count = 0;
unsigned char Object::key;
int Object::specialKey;

unsigned int Object::meterialBlockLoaction;

Object::Object(): transform()
{
	id = ID_Count++;
	name = "UnName";
	isActive = true;

	allObject.push_back(this);
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

mat4& Object::SetMatrix()
{
	mat4 worldModel = mat4(1.0);
	mat4 localModel = mat4(1.0);

	localModel = translate(localModel, transform.localPivot);
	localModel = translate(localModel, transform.localPosition);
	localModel = rotate(localModel, radians(transform.localRotation.x), vec3(1.0, 0, 0));
	localModel = rotate(localModel, radians(transform.localRotation.y), vec3(0, 1.0, 0));	// y축으로 자전 해주고 싶어 처음에 추가
	localModel = rotate(localModel, radians(transform.localRotation.z), vec3(0, 0, 1.0));
	localModel = scale(localModel, transform.localScale);

	worldModel = translate(worldModel, transform.worldPivot);
	worldModel = translate(worldModel, transform.worldPosition);
	worldModel = rotate(worldModel, radians(transform.worldRotation.x), vec3(1.0, 0, 0));
	worldModel = rotate(worldModel, radians(transform.worldRotation.y), vec3(0, 1.0, 0));
	worldModel = rotate(worldModel, radians(transform.worldRotation.z), vec3(0, 0, 1.0));
	worldModel = scale(worldModel, transform.worldScale);

	transform.model = localModel * worldModel;

	return transform.model;
}