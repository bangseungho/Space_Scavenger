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
	// Motion ���� ���콺 ��ġ�� �޾ƿ´�.
	// ���콺�� Button ���� �ö� ������ A ���� �����ش�.
	// ���콺�� Button ���� �ö� ���� ������ A ���� ������ ������ �ٲپ��ش�.
}

void Button::CheckClick()
{
	// Mouse ���� ��ġ�� ���¸� �޾ƿ´�.
	// Ŭ�������� ��ġ�� �´ٸ� Mark �� Active�� On/Off ���ش�.
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