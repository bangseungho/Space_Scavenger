#include "Gauge.h"

Gauge::Gauge()
{
	name = "Gauge";
	image_file = "gauge.png";

	// 초기 위치, 크기 설정
	transform.local->scale -= 0.3;
	transform.local->scale.x = 0;
	transform.local->position.x += 0;
	transform.local->position.y += 0.9;
}

Gauge::~Gauge()
{
}

void Gauge::Init()
{
	GuiObject::Init();
	guiRender::gui_objectRender->AddObject(this);
}
