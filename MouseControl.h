#pragma once
#include "Afx.h"
class MouseControl
{
public:
	static vector<MouseControl*> allMouseControl;
public:
	MouseControl();
	~MouseControl();

public:
	void (*MouseEvent)(int button, int state, int x, int y);
	void (*MouseWheelEvent)(int wheel, int direction, int x, int y);
	void (*MotionEvent)(int x, int y);
	void (*MouseEntryEvent)(int state);
};

