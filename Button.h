#pragma once
#include "Render.h"

#pragma region Image
class ButtonDefualt : public Object, public UIMesh
{
public:
	ButtonDefualt() : UIMesh(this) {
		name += " Default";
		Render::uiRender->AddObject(this);
	}
};

class ButtonOnMouse : public Object, public UIMesh
{
public:
	ButtonOnMouse() : UIMesh(this) {
		name += " Default";
		SetActive(false);
		Render::uiRender->AddObject(this);
	}
};
class ButtonClick : public Object, public UIMesh
{
public:
	ButtonClick() : UIMesh(this) {
		name += " Default";
		SetActive(false);
		Render::uiRender->AddObject(this);
	}
};
#pragma endregion


class Button : public Object
{
public:
	Button() : Button("UI/Button/Default/") {};
	Button(string path);
	~Button();

public:
	void Init();
	void Update();

public:
	void CheckOnMouse();
	void CheckClick();
	bool CheckInMouse();
public:
	bool isClick;
	bool isToggle;
private:
	ButtonDefualt ui_Defualt;
	ButtonOnMouse ui_OnMouse;
	ButtonClick ui_Click;

	int width;
	int height;
};

