#include "GameManager.h"

GameManager::GameManager()
{

}
GameManager::~GameManager()
{

}

void GameManager::Init()
{
	StartMouse = vec2(0);

	isMouseRight = false;

	Camera::mainCamera->target_Pos = &player.transform;
	light.transform.local->position.x = 1;

	bgm.Load("Sound/ItemEarn.wav");
	bgm.RepetPlay();
}

void GameManager::Update()
{
	//if (!harpoon.firing) {
	//	harpoon.transform.worldPosition = Camera::mainCamera->cameraPos;
	//	harpoon.transform.worldPosition.z -= 2.5;
	//	harpoon.transform.worldPosition.y -= 1;
	//}
}

void GameManager::SpecialKeyboardUp(int key, int x, int y)
{
}

void GameManager::Mouse(int button, int state, int x, int y)
{
	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;

	vec2 realStartMouse = RealPosition(StartMouse);

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		isMouseRight = !isMouseRight;
	}
}

void GameManager::MouseWheel(int wheel, int direction, int x, int y)
{
	if (direction < 0)
	{
		cout << "Zoom out" << endl;
		Camera::mainCamera->LookAtView(1);
	}
	else
	{
		cout << "Zoom in " << endl;
		Camera::mainCamera->LookAtView(-1);
	}
}


void GameManager::Motion(int x, int y)
{
	vec2 mouse_Pos = { (float)x, (float)y };
	mouse_Pos = Coordinate(mouse_Pos);
	mouse_Pos.y = -mouse_Pos.y;

	//ShowCursor(isMouseRight);
	if (!isMouseRight)
	{
		vec2 diffPos = (mouse_Pos - StartMouse);
		player.FaceMove(diffPos);
		//vec2 diffPos = (mouse_Pos - StartMouse) * FrameTime::oneFrame;
		//player.transform.worldRotation.y -= diffPos.x;
		//player.transform.worldRotation.x += diffPos.y;
	}

	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;
}

void GameManager::MouseEntry(int state)
{
	if (state == GLUT_LEFT)
	{
		if (!isMouseRight)
		{
			glutWarpPointer(windowSize_W / 2, windowSize_H / 2);
			StartMouse = { (float)windowSize_W / 2, (float)windowSize_H / 2 };
			StartMouse = Coordinate(StartMouse);
			StartMouse.y = -StartMouse.y;
		}
	}
}