#include "SpeedGauge.h"

SpeedGauge::SpeedGauge(SpeedBlock* _Speed) : speedBlock(_Speed)
{
	ui_Panel.image_file = "UI/Player/Panner.png";
	ui_PanelBack.image_file = "UI/Player/PannerBack.png";
	ui_Gauge.image_file = "UI/Player/Guage.png";

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
		ui_PanelBack.transform.world.push_back(world);
		ui_Gauge.transform.world.push_back(world);
	}
	ui_Panel.transform.world.push_back(transform.local);
	ui_PanelBack.transform.world.push_back(transform.local);
	ui_Gauge.transform.world.push_back(transform.local);
}

void SpeedGauge::Update()
{
	float xScale = speedBlock->current / speedBlock->max;
	ui_Gauge.transform.local->scale.x = xScale;
	ui_Gauge.transform.local->position.x = (xScale - 1.0f) * 0.5f * ui_Gauge.width;

	if(xScale > 0 && xScale < 0.3f)
		ui_Gauge.color.SetColor({ 0,1,0,1 });
	else if (xScale > 0.3f && xScale < 0.7f)
		ui_Gauge.color.SetColor({ 0,0,1,1 });
	else if (xScale > 0.7f)
		ui_Gauge.color.SetColor({ 1,0,0,1 });
}