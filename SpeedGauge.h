#pragma once
#include "Render.h"

struct SpeedBlock {
	float max;	// �ִ� ���ǵ�
	float accelerat;	// ���ӵ�
	float current;	// ���� �ӵ�
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

