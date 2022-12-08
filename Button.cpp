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
	// Motion ���� ���콺 ��ġ�� �޾ƿ´�.
	// ���콺�� Button ���� �ö� ������ A ���� �����ش�.
	// ���콺�� Button ���� �ö� ���� ������ A ���� ������ ������ �ٲپ��ش�.
}

void Button::CheckClick()
{
	// Mouse ���� ��ġ�� ���¸� �޾ƿ´�.
	// Ŭ�������� ��ġ�� �´ٸ� Mark �� Active�� On/Off ���ش�.
}

ButtonMark::ButtonMark()
{
	name = "Button Mark";
	SetActive(false);
}

ButtonMark::~ButtonMark()
{
}