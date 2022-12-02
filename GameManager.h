#pragma once
#include "Cube.h"
#include "Player.h"
#include "Map.h"
#include "ChatBox.h"
//#include "ResourcePool.cpp"	// 템플릿 클래스는 cpp를 인클루드 해야함
#include "Iron.h"
#include "Light.h"
#include "Equipment.h"
#include "Gauge.h"
class GameManager : public Object
{
public:
	Cube cube_Obj;
	Player player;
	Map map;
	ChatBox chat_box;
	Light light;
	//Equipment harpoon;
	//Gauge gauge;

public:
	void Init();

	void Update();
};

