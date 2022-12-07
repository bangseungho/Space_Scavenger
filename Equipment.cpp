#include "Equipment.h"

Equipment::Equipment() : Mesh(this)
{
	myType = EqType::HARPOON;
	myState = State::IDLE;

	isDragged = false;
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



void Equipment::ChargingEnergy()
{
}

void Equipment::FinishCharging()
{
}

void Equipment::Update()
{
}