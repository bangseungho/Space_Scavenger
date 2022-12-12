#include "Toggle.h"

Toggle::Toggle(string path)
{
	name = "Button";

	isToggle = false;

	ui_UnMark.image_file = path + "Default.png";
	ui_Mark.image_file = path + "OnMouse.png";
}

Toggle::~Toggle()
{
}

void Toggle::Enable()
{
	ui_UnMark.SetActive(!isToggle);
	ui_Mark.SetActive(isToggle);
}

void Toggle::Disable()
{
	ui_UnMark.SetActive(false);
	ui_Mark.SetActive(false);
}

void Toggle::Init()
{
	for (const auto& world : transform.world)
	{
		ui_UnMark.transform.world.push_back(world);
		ui_Mark.transform.world.push_back(world);
	}
	ui_UnMark.transform.world.push_back(transform.local);
	ui_Mark.transform.world.push_back(transform.local);

	width = ui_UnMark.width;
	height = ui_UnMark.height;
}

void Toggle::Update()
{
	if (!CheckInMouse())
		return;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (!CheckInMouse())
			return;

		ui_UnMark.SetActive(!ui_UnMark.ActiveSelf());
		ui_Mark.SetActive(!ui_Mark.ActiveSelf());
		isToggle = !isToggle;
	}
}

bool Toggle::CheckInMouse()
{
	vec2 pos[2];
	pos[0] = transform.model * vec4(-width / 2, -height / 2, 0, 1); // bottom left
	pos[1] = transform.model * vec4(width / 2, height / 2, 0, 1); // top right
	if (mouse_Pos.x < pos[0].x) return false;
	if (mouse_Pos.y < pos[0].y) return false;
	if (mouse_Pos.x > pos[1].x) return false;
	if (mouse_Pos.y > pos[1].y) return false;
	return true;
}
