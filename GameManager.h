#pragma once
#include "Cube.h"
#include "Player.h"
#include "Map.h"
#include "ChatBox.h"
//#include "ResourcePool.cpp"	// 템플릿 클래스는 cpp를 인클루드 해야함
#include "Iron.h"
#include "Light.h"
#include "Gauge.h"
#include "Sound.h"

class GameManager : public Object
{
public:
	GameManager();
	~GameManager();
public:
	void Init();
	void Update();
	void KeyBoard(unsigned char key, int x, int y);
	void SpecialKeyBoard(int key, int x, int y);
	void SpecialKeyboardUp(int key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void MouseWheel(int wheel, int direction, int x, int y);
	void Motion(int x, int y);
	void MouseEntry(int state);

public:
	Cube cube_Obj;
	Player player;
	Map map;
	ChatBox chat_box;
	Light light;
	//Gauge gauge;

private:
	bool isMouseRight;
	vec2 StartMouse;

	Sound bgm;	// 임시
};

