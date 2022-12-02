#include "GameManager.h"

void GameManager::Init()
{
	Camera::mainCamera->target_Pos = &player.transform;
	cube_Obj.transform.worldScale *= 0.1;
	light.transform.worldPosition.x = 1;
}

void GameManager::Update()
{
	//if (!harpoon.firing) {
	//	harpoon.transform.worldPosition = Camera::mainCamera->cameraPos;
	//	harpoon.transform.worldPosition.z -= 2.5;
	//	harpoon.transform.worldPosition.y -= 1;
	//}
}
