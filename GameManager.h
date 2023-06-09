#pragma once
#include "Player.h"
#include "PlanetManager.h"
#include "SoundManager.h"
#include "ChatBox.h"

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
	SoundManager soundManager;
	PlanetManager planetManager[3] = {
		PlanetManager{ 1500,5000 },
		PlanetManager{5000,15000},
		PlanetManager{20000,30000} 
	};
public:
	Player player;
	ChatBox chat;

private:
	bool isMouseRight;

	// Special Key
	bool isALT_L;

	Sound bgm;
};

