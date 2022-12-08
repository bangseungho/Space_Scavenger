#pragma once
#include "GuiRender.h"

class ButtonMark : public GuiObject
{
public:
	ButtonMark();
	~ButtonMark();

};

class Button : public GuiObject
{
public:
	Button();
	~Button();

public:
	void Update();

public:
	void CheckOnMouse();
	void CheckClick();

public:
	ButtonMark mark;

};

