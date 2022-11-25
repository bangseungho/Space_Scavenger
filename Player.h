#pragma once
#include "Render.h"
#include "Collider.h"

#include "Cube.h"
class Player : public Object
{
public:
	static Player* Instance;
	static ObjectBlock* _Block;

public:
	Player();
	~Player();

public:
	void Init();
	void Update();
	void Handle_Evnet(unsigned char key);
	void Handle_Evnet(int specialKey);
	void Collision();

private: // MouseEvent
	//void MouseWheelEvent(int wheel, int direction, vec2 pos);

public:
	Collider collider;
	float speed = 1;

};

