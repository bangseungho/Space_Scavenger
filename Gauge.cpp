#include "Gauge.h"

Gauge::Gauge() 
{
	name = "Gauge";
	ReadImage("gauge.png");
	/*image_file = "gauge.png";*/

	// �ʱ� ��ġ, ũ�� ����
	transform.localScale -= 0.3;
	transform.localScale.x = 0;
	transform.localPosition.x += 0;
	transform.localPosition.y += 0.9;

	guiRender::gui_objectRender->AddObject(this);
}

Gauge::~Gauge()
{
}
