#pragma once
#include "Render.h"
#include "Image.h"

struct SpeedBlock {
	float max;	// 최대 스피드
	float accelerat;	// 가속도
	float current;	// 현재 속도
};

class SpeedGauge : public Object
{
public:
	SpeedGauge(SpeedBlock* _Speed);
	~SpeedGauge();

public:
	void Init();
	void Update();

private:
	Image ui_PannelBack;
	Image ui_Gauge;
	Image ui_Pannel;

private:
	SpeedBlock* speedBlock;
};

