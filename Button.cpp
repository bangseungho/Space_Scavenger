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
	// Motion ���� ���콺 ��ġ�� �޾ƿ´�.
	// ���콺�� Button ���� �ö� ������ A ���� �����ش�.
	// ���콺�� Button ���� �ö� ���� ������ A ���� ������ ������ �ٲپ��ش�.

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
	// Mouse ���� ��ġ�� ���¸� �޾ƿ´�.
	// Ŭ�������� ��ġ�� �´ٸ� Mark �� Active�� On/Off ���ش�. (���� �̰� ��Ŭ ��ư�̶��)

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
