#include "Gauge.h"

Gauge::Gauge() : UIMesh(this)
{
	name = "Gauge";
	image_file = "gauge.png";

	// �ʱ� ��ġ, ũ�� ����
	transform.local->scale -= 0.3;
	transform.local->scale.x = 0;
	transform.local->position.x += 0;
	transform.local->position.y += 0.9;

	Render::uiRender->AddObject(this);
}

Gauge::~Gauge()
{
}