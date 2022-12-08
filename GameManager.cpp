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

	bgm.Load("Sound/bgm.mp3", true);
	effect.Load("Sound/ItemEarn.wav", false);

	all_sound.push_back(&bgm);
	all_sound.push_back(&effect);

	bgm.Play();
}

void GameManager::Update()
{
}

void GameManager::SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_ALT_L:
		isALT_L = true;
		Camera::mainCamera->cameraDirection = vec3(0);
		break;
	case GLUT_KEY_F1:
		effect.Play();
		break;
	case GLUT_KEY_F2:
		for (auto a : all_sound) a->Stop();
		break;
	case GLUT_KEY_F3:
		for (auto a : all_sound) a->Play();
		break;
	case GLUT_KEY_F5:
		for (auto a : all_sound) a->SetVolum(-0.1);
		break;
	case GLUT_KEY_F6:
		for (auto a : all_sound) a->SetVolum(0.1);
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
		if (isALT_L)
		{
			vec2 speed = vec2(15, 10);
			vec2 fMoveSpeed = diffPos * FrameTime::oneFrame * speed;
			Camera::mainCamera->transform.local->rotation.x -= fMoveSpeed.y;
			Camera::mainCamera->transform.local->rotation.y -= fMoveSpeed.x;
		}
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