#pragma once
#include "Cube.h"
#include "Player.h"
#include "Map.h"
#include "ChatBox.h"
//#include "ResourcePool.cpp"	// ���ø� Ŭ������ cpp�� ��Ŭ��� �ؾ���
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

