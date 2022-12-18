#pragma once
#include "Render.h"
#include "Image.h"

struct SpeedBlock {
	float max;	// �ִ� ���ǵ�
	float accelerat;	// ���ӵ�
	float current;	// ���� �ӵ�
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

