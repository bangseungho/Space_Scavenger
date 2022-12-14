#include "Gauge.h"

Gauge::Gauge() : UIMesh(this)
{
	name = "Gauge";
	image_file = "gauge.png";

	// 초기 위치, 크기 설정
	transform.local->scale -= 0.3;
	transform.local->scale.x = 0;
	transform.local->position.x += 0;
	transform.local->position.y = 0.9;

	//transform.model *= vec4(0, 0.9, 0, 1); // bottom left


	Render::uiRender->AddObject(this);

}

Gauge::~Gauge()
{
}