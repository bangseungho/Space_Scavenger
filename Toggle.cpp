#include "Toggle.h"

Toggle::Toggle(string path)
{
	name = "Button";

	sound_Click.Load("Sound/Button/Default/Click.wav");
	sound_Click.channelType = "Effect";

	// Member º¯¼ö
	isToggle = false;

	ui_Mark.image_file = path + "Mark.png";
	ui_UnMark.image_file = path + "UnMark.png";

	font.lineType = 1;
}

Toggle::~Toggle()
{
}

void Toggle::Enable()
{
	ui_UnMark.SetActive(!isToggle);
	ui_Mark.SetActive(isToggle);
	font.SetActive(true);
}

void Toggle::Disable()
{
	ui_UnMark.SetActive(false);
	ui_Mark.SetActive(false);
	font.SetActive(false);
}

void Toggle::Init()
{
	for (const auto& world : transform.world)
	{
		ui_UnMark.transform.world.push_back(world);
		ui_Mark.transform.world.push_back(world);
		font.transform.world.push_back(world);
	}
	ui_UnMark.transform.world.push_back(transform.local);
	ui_Mark.transform.world.push_back(transform.local);
	font.transform.world.push_back(transform.local);

	size = ui_UnMark.size;
}

void Toggle::Update()
{
	ui_UnMark.color = color;
	ui_Mark.color = color;
	if (!CheckInMouse())
		return;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (!CheckInMouse())
			return;

		ToggleClick();
	}
}

void Toggle::ToggleClick()
{
	ui_UnMark.SetActive(!ui_UnMark.ActiveSelf());
	ui_Mark.SetActive(!ui_Mark.ActiveSelf());
	isToggle = !isToggle;

	sound_Click.Play();
}

bool Toggle::CheckInMouse()
{
	vec2 pos[2];
	pos[0] = transform.model * vec4(-size->width / 2, -size->height / 2, 0, 1); // bottom left
	pos[1] = transform.model * vec4(size->width / 2, size->height / 2, 0, 1); // top right
	if (mouse_Pos.x < pos[0].x) return false;
	if (mouse_Pos.y < pos[0].y) return false;
	if (mouse_Pos.x > pos[1].x) return false;
	if (mouse_Pos.y > pos[1].y) return false;
	return true;
}
