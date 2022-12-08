#include "Gauge.h"

Gauge::Gauge() 
{
	name = "Gauge";
	ReadImage("gauge.png");
	/*image_file = "gauge.png";*/

	// 초기 위치, 크기 설정
	transform.localScale -= 0.3;
	transform.localScale.x = 0;
	transform.localPosition.x += 0;
	transform.localPosition.y += 0.9;

	guiRender::gui_objectRender->AddObject(this);
}

Gauge::~Gauge()
{
}
