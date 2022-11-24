#pragma once
#include "Cube.h"
class Player : public Cube
{
public:
	static Player* Instance;

public:
	Player();
	~Player();

public:
	void Init();
	void Update();
	void Handle_Evnet(unsigned char key);
	void Handle_Evnet(int specialKey);
	void Collision();

public:
	float speed = 1;
};

