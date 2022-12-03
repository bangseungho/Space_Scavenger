#include "Equipment.h"

void Equipment::SetType(EqType type)
{
	myType = type;
}

EqType Equipment::GetType()
{
	return this->myType;
}

Equipment::Equipment() : Mesh(this)
{
}

void Equipment::Init()
{
}

Equipment::~Equipment()
{
}

void Equipment::Update()
{
}