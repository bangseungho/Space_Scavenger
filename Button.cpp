#include "Button.h"

Button::Button() 
{
	name = "Button";

	isToggle = false;
}

Button::~Button()
{
}

void Button::Init()
{
	for (const auto& world : transform.world)
	{
		unMark.transform.world.push_back(world);
		mark.transform.world.push_back(world);
	}
	unMark.transform.world.push_back(transform.local);
	mark.transform.world.push_back(transform.local);
}

void Button::Update()
{
	CheckOnMouse();
	CheckClick();
}

void Button::CheckOnMouse()
{	
	// Motion 에서 마우스 위치를 받아온다.
	// 마우스가 Button 위에 올라가 있으면 A 값을 낮춰준다.
	// 마우스가 Button 위에 올라가 있지 않으면 A 값을 본래의 값으로 바꾸어준다.
}

void Button::CheckClick()
{
	// Mouse 에서 위치와 상태를 받아온다.
	// 클릭했을때 위치가 맞다면 Mark 의 Active를 On/Off 해준다.
}

#pragma region Button_Image

ButtonMark::ButtonMark() : UIMesh(this)
{
	name = "Button Mark";
	image_file = "UI/Button/Mark.png";
	SetActive(false);

	Render::uiRender->AddObject(this);
}

ButtonMark::~ButtonMark()
{
}

ButtonUnMark::ButtonUnMark() : UIMesh(this)
{
	name = "Button UnMark";
	image_file = "UI/Button/UnMark.png";

	Render::uiRender->AddObject(this);
}

ButtonUnMark::~ButtonUnMark()
{
}

#pragma endregion