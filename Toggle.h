#pragma once
#include "Render.h"

class ToggleUnMark : public Object, public UIMesh
{
public:
	ToggleUnMark() : UIMesh(this) {
		name = "Toggle UnMark";
		Render::uiRender->AddObject(this, "Toggle");
	}
};

class ToggleMark : public Object, public UIMesh
{
public:
	ToggleMark() : UIMesh(this) {
		name = "Toggle Mark";
		SetActive(false);
		Render::uiRender->AddObject(this, "Toggle");
	}
};

class Toggle : public Object
{
public:
	Toggle() : Toggle("UI/Toggle/Default/") {};
	Toggle(string path);
	~Toggle();

public:
	void Enable();
	void Disable();
	void Init();
	void Update();

private:
	bool CheckInMouse();

public:
	Color color;
	bool isToggle;

private:
	ToggleUnMark ui_UnMark;
	ToggleMark ui_Mark;

	int width;
	int height;
};

