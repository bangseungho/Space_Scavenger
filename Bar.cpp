#include "Bar.h"

Bar::Bar()
{
	name = "Bar";
	ui_Bar.image_file = "UI/Setting/Sound/Bar.png";
	ui_Guage.image_file = "UI/Setting/Sound/Button.png";
	sound_Click.Load("Sound/Button/Default/Click.wav");

	isPress = false;
	amount = 0.5f;
}

Bar::~Bar()
{
}

void Bar::Enable()
{
	ui_Bar.SetActive(true);
	ui_Guage.SetActive(true);
}

void Bar::Disable()
{
	ui_Bar.SetActive(false);
	ui_Guage.SetActive(false);
}

void Bar::Init()
{
	for (const auto& world : transform.world)
	{
		ui_Bar.transform.world.push_back(world);
		ui_Guage.transform.world.push_back(world);
	}
	ui_Bar.transform.world.push_back(transform.local);
	ui_Guage.transform.world.push_back(transform.local);

	size = ui_Bar.size;
	guage_Size = ui_Guage.size;
}

void Bar::Update()
{
	CheckPress();
	float s = size->width - guage_Size->width * 2;
	if (isPress)
	{
		float x = mouse_Pos.x;
		amount = x / s + 0.5f;
		cout << mouse_Pos.x << endl;
		cout << amount << endl;
	}

	if (amount > 1) amount = 1;
	else if (amount < 0) amount = 0;
	ui_Guage.transform.local->position.x = (amount - 0.5f) * (s);
}

bool Bar::CheckInMouse()
{
	vec2 pos[2];
	pos[0] = ui_Guage.transform.model * vec4(-guage_Size->width / 2, -guage_Size->height / 2, 0, 1); // bottom left
	pos[1] = ui_Guage.transform.model * vec4(guage_Size->width / 2, guage_Size->height / 2, 0, 1); // top right
	if (mouse_Pos.x < pos[0].x) return false;
	if (mouse_Pos.y < pos[0].y) return false;
	if (mouse_Pos.x > pos[1].x) return false;
	if (mouse_Pos.y > pos[1].y) return false;
	return true;
}

void Bar::CheckPress()
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (isPress) return;
		if (!CheckInMouse()) return;

		sound_Click.Play();
		isPress = true;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		isPress = false;
	}
}
