#include "Button.h"
Button::Button(string path)
{
	name = "Button";

	isClick = false;
	isToggle = false;

	ui_Defualt.image_file = path + "Default.png";
	ui_OnMouse.image_file = path + "OnMouse.png";
	ui_Click.image_file = path + "Click.png";
}

Button::~Button()
{
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
	ui_Defualt.SetActive(true);
	ui_OnMouse.SetActive(false);
	ui_Click.SetActive(false);
	CheckOnMouse();
	CheckClick();
}

void Button::CheckOnMouse()
{	
	// Motion 에서 마우스 위치를 받아온다.
	// 마우스가 Button 위에 올라가 있으면 A 값을 낮춰준다.
	// 마우스가 Button 위에 올라가 있지 않으면 A 값을 본래의 값으로 바꾸어준다.

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		return;

	vec2 pos[2];
	pos[0] = transform.model * vec4(-width / 2, -height / 2, 0, 1); // bottom left
	pos[1] = transform.model * vec4(width / 2, height / 2, 0, 1); // top right
	if (mouse_Pos.x < pos[0].x) return;
	if (mouse_Pos.y < pos[0].y) return;
	if (mouse_Pos.x > pos[1].x) return;
	if (mouse_Pos.y > pos[1].y) return;

	ui_Defualt.SetActive(false);
	ui_OnMouse.SetActive(true);
	ui_Click.SetActive(false);
}

void Button::CheckClick()
{
	// Mouse 에서 위치와 상태를 받아온다.
	// 클릭했을때 위치가 맞다면 Mark 의 Active를 On/Off 해준다. (만약 이게 토클 버튼이라면)

	isClick = false;
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;

	vec2 pos[2];
	pos[0] = transform.model * vec4(-width / 2, -height / 2, 0, 1); // bottom left
	pos[1] = transform.model * vec4(width / 2, height / 2, 0, 1); // top right
	if (mouse_Pos.x < pos[0].x) return;
	if (mouse_Pos.y < pos[0].y) return;
	if (mouse_Pos.x > pos[1].x) return;
	if (mouse_Pos.y > pos[1].y) return;

	ui_Defualt.SetActive(false);
	ui_OnMouse.SetActive(false);
	ui_Click.SetActive(true);
	isClick = true;
}
