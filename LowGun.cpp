#include "LowGun.h"

OBJ* LowGun::_Obj = nullptr;

LowGun::LowGun()
{
	SetType(EqType::LOWGUN);
	name = "Lowgun";

	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj((char*)"Sphere.obj");
	}
	
	transform.local->scale = vec3(0.1);
	obj = _Obj;

	Render::objectRender->AddObject(this, "Lowgun");
}

LowGun::~LowGun()
{
}

void LowGun::Update()
{
}

void LowGun::Fire()
{
	cout << "FIRED!!!" << endl;
	bullet.transform = transform;
	bullet.SetActive(true);
}