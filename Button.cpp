#include "Button.h"

Button::Button() 
{
	name = "Button";
}

Button::~Button()
{
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

ButtonMark::ButtonMark()
{
	name = "Button Mark";
	SetActive(false);
}

ButtonMark::~ButtonMark()
{
}