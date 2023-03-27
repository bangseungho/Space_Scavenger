#pragma once
#include "Object.h"
#include "Image.h"
#include "Sound.h"
class Bar : public Object
{
public:
	Bar();
	~Bar();

public:
	void Enable();
	void Disable();
	void Init();
	void Update();

private:
	bool CheckInMouse();
	void CheckPress();

public:
	bool isPress;

	float amount;

	ImageSize* size;
private:
	Image ui_Bar;
	Image ui_Guage;

	Sound sound_Click;

	ImageSize* guage_Size;
};

