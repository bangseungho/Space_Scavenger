#include "Button.h"
Button::Button(string path)
{
	name = "Button";

	isClick = false;

	ui_Defualt.image_file = path + "Default.png";
	ui_OnMouse.image_file = path + "OnMouse.png";
	ui_Click.image_file = path + "Click.png";
}

Button::~Button()
{
}

void Button::Enable()
{
	ui_Defualt.SetActive(true);
}

void Button::Disable()
{
	ui_Defualt.SetActive(false);
	ui_OnMouse.SetActive(false);
	ui_Click.SetActive(false);
	isClick = false;
}

void Button::Init()
{
	for (const auto& world : transform.world)
	{
		ui_Defualt.transform.world.push_back(world);
		ui_OnMouse.transform.world.push_back(world);
		ui_Click.transform.world.push_back(world);
	}
	ui_Defualt.transform.world.push_back(transform.local);
	ui_OnMouse.transform.world.push_back(transform.local);
	ui_Click.transform.world.push_back(transform.local);

	width = ui_Defualt.width;
	height = ui_Defualt.height;
}

void Button::Update()
{
	CheckOnMouse();
	CheckClick();
}

void Button::CheckOnMouse()
{	
	if (ui_Click.ActiveSelf())
		return;

	ui_Defualt.SetActive(true);
	ui_OnMouse.SetActive(false);
	ui_Click.SetActive(false);

	if (!CheckInMouse())
		return;

	ui_Defualt.SetActive(false);
	ui_OnMouse.SetActive(true);
	ui_Click.SetActive(false);
}

void Button::CheckClick()
{
	if (ui_Defualt.ActiveSelf())
		return;

	isClick = false;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (!CheckInMouse())
			return;

		ui_Defualt.SetActive(false);
		ui_OnMouse.SetActive(false);
		ui_Click.SetActive(true);
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (CheckInMouse())
		{
			ui_Click.SetActive(false);
			isClick = true;
		}
	}
}

bool Button::CheckInMouse()
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
