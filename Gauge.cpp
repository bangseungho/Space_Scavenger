#include "Gauge.h"

Gauge::Gauge()
{
	name = "Gauge";
	image_file = "gauge.png";

	// 초기 위치, 크기 설정
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
