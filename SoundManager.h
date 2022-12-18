#pragma once
#include "Button.h"
#include "Bar.h"
#include "BackGround.h"

class SoundBar;

class SoundManager : public Object
{
public:
	static SoundManager* Instace;

public:
	SoundManager();
	~SoundManager();

public:
	void Enable();
	void Disable();
	void Init();

private:
	BackGround bacground{"UI/Setting/Sound/", "BackGround.png"};
	SoundBar* bar_Music;
	SoundBar* bar_Effect;
};

class SoundBar : public Object
{
public:
	SoundBar();
	~SoundBar();

public:
	void Enable();
	void Disable();
	void Init();
	void Update();

public:
	string type; // what kind of sound
private:
	Font font;
	Bar bar;
	Button plus_Button{ "UI/Setting/Sound/Button/Plus/" };
	Button minus_Button{ "UI/Setting/Sound/Button/Minus/" };
};
