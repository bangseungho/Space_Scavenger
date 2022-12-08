#include "Object.h"

//list<Object*> Object::allObject;	//main.cpp 에서 전역변수로 Object 호출시 static 부분 무시함 (이유는 모름)
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
	mat4 lModel = mat4(1.0);

	lModel = translate(lModel, transform.localPivot);
	lModel = translate(lModel, transform.localPosition);
	lModel = rotate(lModel, radians(transform.localRotation.x), vec3(1.0, 0, 0));
	lModel = rotate(lModel, radians(transform.localRotation.y), vec3(0, 1.0, 0));
	lModel = rotate(lModel, radians(transform.localRotation.z), vec3(0, 0, 1.0));
	lModel = scale(lModel, transform.localScale);

	*transform.localModel = lModel;
	*transform.model = (*transform.worldModel) * (lModel);

	return *transform.model;
}