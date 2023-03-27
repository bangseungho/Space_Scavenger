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

	bgm.Load("Sound/bgm.mp3", true);
	bgm.RepeatPlay();
}

void GameManager::Update()
{
}

void GameManager::KeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // Escape key
		soundManager.SetActive(!soundManager.ActiveSelf());
		break;
	}
}

void GameManager::SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_ALT_L:
		isALT_L = true;
		Camera::mainCamera->cameraDirection = vec3(0);
		break;
	}
}

void GameManager::SpecialKeyboardUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_ALT_L:
		isALT_L = false;
		Camera::mainCamera->transform.local->ReSet();
		Camera::mainCamera->cameraDirection.z = 4;
		break;
	default:
		break;
	}
}


void GameManager::Mouse(int button, int state, int x, int y)
{
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
		//cout << "Zoom out" << endl;
		Camera::mainCamera->LookAtView(3);
	}
	else
	{
		vec3 cameraPos = (Camera::mainCamera->transform.local->position + Camera::mainCamera->cameraPos) * Camera::mainCamera->target_Pos->local->scale;
		if (length(cameraPos - Camera::mainCamera->cameraDirection) < 7)
			return;
		//cout << "Zoom in " << endl;
		Camera::mainCamera->LookAtView(-3);
	}
}


void GameManager::Motion(int x, int y)
{
	//ShowCursor(isMouseRight);
	if (!isMouseRight)
	{
		vec2 diffPos = (mouse_Pos - StartMouse);
		player.FaceMove(diffPos);
		if (isALT_L)
		{
			vec2 speed = vec2(15, 10);
			vec2 fMoveSpeed = diffPos * FrameTime::oneFrame * speed;
			Camera::mainCamera->transform.local->rotation.x -= fMoveSpeed.y;
			Camera::mainCamera->transform.local->rotation.y -= fMoveSpeed.x;
		}
		mouse_Pos = { (float)windowSize_W / 2, (float)windowSize_H / 2 };
		mouse_Pos = Coordinate(mouse_Pos);
		mouse_Pos.y = -mouse_Pos.y;
		glutWarpPointer(windowSize_W / 2, windowSize_H / 2);
	}
}

void GameManager::MouseEntry(int state)
{
}