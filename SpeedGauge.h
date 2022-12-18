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
	Image ui_Panel;
	Image ui_PanelBack;
	Image ui_Gauge;

private:
	SpeedBlock* speedBlock;
};

