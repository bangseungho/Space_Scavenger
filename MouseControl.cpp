#include "MouseControl.h"

vector<MouseControl*> MouseControl::allMouseControl;

MouseControl::MouseControl()
{
	allMouseControl.push_back(this);
}

MouseControl::~MouseControl()
{
}

//void MouseControl::Mouse(int button, int state, int x, int y)
//{
//}
//
//void MouseControl::MouseWheel(int wheel, int direction, int x, int y)
//{
//}
//
//void MouseControl::Motion(int x, int y)
//{
//}
//
//void MouseControl::MouseEntry(int state)
//{
//}
