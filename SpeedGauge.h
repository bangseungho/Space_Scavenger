#pragma once
#include "Render.h"

struct SpeedBlock {
	float max;	// 최대 스피드
	float accelerat;	// 가속도
	float current;	// 현재 속도
};

class SpeedGauge : public Object
{
	class Panel : public Object, public UIMesh {
	public:
		Panel();
	};

	class Gauge : public Object, public UIMesh {
	public:
		Gauge();
	};

public:
	SpeedGauge(SpeedBlock* _Speed);
	~SpeedGauge();

public:
	void Init();
	void Update();

private:
	Panel ui_Panel;
	Gauge ui_Gauge;

private:
	SpeedBlock* speedBlock;
};

