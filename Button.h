#pragma once
#include "Render.h"

class ButtonMark : public Object, public UIMesh
{
public:
	ButtonMark();
	~ButtonMark();
};

class ButtonUnMark : public Object, public UIMesh
{
public:
	ButtonUnMark();
	~ButtonUnMark();
};

class Button : public Object
{
public:
	Button();
	~Button();

public:
	void Init();
	void Update();

public:
	void CheckOnMouse();
	void CheckClick();

public:
	bool isToggle;

private:
	ButtonUnMark unMark;
	ButtonMark mark;

};

