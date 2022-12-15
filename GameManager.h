#pragma once
#include "Player.h"
#include "Map.h"
#include "ChatBox.h"
#include "Iron.h"
#include "Light.h"
#include "Gauge.h"
#include "Sound.h"
#include "Button.h"
#include "PlanetManager.h"

class GameManager : public Object
{
public:
	GameManager();
	~GameManager();
public:
	void Init();
	void Update();
	void KeyBoard(unsigned char key, int x, int y);
	void SpecialKeyboard(int key, int x, int y);
	void SpecialKeyboardUp(int key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void MouseWheel(int wheel, int direction, int x, int y);
	void Motion(int x, int y);
	void MouseEntry(int state);

public:
	PlanetManager planetManager;
public:
	Player player;

private:
	bool isMouseRight;

	// Special Key
	bool isALT_L;

	Sound bgm;
};

