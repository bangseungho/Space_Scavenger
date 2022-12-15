#include "SpeedGauge.h"

SpeedGauge::SpeedGauge(SpeedBlock* _Speed) : speedBlock(_Speed)
{
	transform.local->scale *= 3;
	transform.local->scale.x *= 2;
	transform.local->position.y = -windowSize_H/2 + 50;
}

SpeedGauge::~SpeedGauge()
{
}

void SpeedGauge::Init()
{
	for (const auto& world : transform.world)
	{
		ui_Panel.transform.world.push_back(world);
		ui_Gauge.transform.world.push_back(world);
	}
	ui_Panel.transform.world.push_back(transform.local);
	ui_Gauge.transform.world.push_back(transform.local);
}

void SpeedGauge::Update()
{
	ui_Gauge.transform.local->scale.x = speedBlock->current / speedBlock->max;
	ui_Gauge.transform.local->position.x = (ui_Gauge.transform.local->scale.x - 1.0f) * 0.5f * ui_Gauge.width;
}

SpeedGauge::Panel::Panel() : UIMesh(this)
{
	name = "Gauge Panel";
	image_file = "UI/Player/GaugePanel.png";
	MeshInit();

	Render::uiRender->AddObject(this);
}

SpeedGauge::Gauge::Gauge() : UIMesh(this)
{
	name = "Gauge";
	image_file = "UI/Player/Gauge.png";
	MeshInit();

	color.SetColor({ 0,0.3,1,1 });

	Render::uiRender->AddObject(this);
}
