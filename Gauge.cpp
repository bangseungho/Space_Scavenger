#include "Gauge.h"

Gauge::Gauge()
{
	name = "Gauge";
	image_file = "gauge.png";

	// �ʱ� ��ġ, ũ�� ����
	transform.localScale -= 0.3;
	transform.localScale.x = 0;
	transform.worldPosition.x += 0;
	transform.worldPosition.y += 0.9;
}

Gauge::~Gauge()
{
}

void Gauge::Init()
{
	GuiObject::Init();
	guiRender::gui_objectRender->AddObject(this);
}
