#pragma once
#include "UIMesh.h"

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
	void Update();

public:
	void CheckOnMouse();
	void CheckClick();

public:
	ButtonMark mark;

};

