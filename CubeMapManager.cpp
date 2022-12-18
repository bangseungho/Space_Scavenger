#include "CubeMapManager.h"

CubeMapManager::CubeMapManager(Transform* _Target) : target_Transform(_Target)
{
	skyIndex = 0;
	offset = 1000;
	skyBox[skyIndex].Load();
}

CubeMapManager::~CubeMapManager()
{

}

//void CubeMapManager::Update()
//{
//	int prevIndex = skyIndex;
//	vec3 dis = target_Transform->model * vec4(0, 0, 0, 1);
//	dis /= vec3(offset);
//	dis.x = int(dis.x);
//	dis.y = int(dis.y);
//	dis.z = int(dis.z);
//	if (dis == vec3(1, 0, 0) || dis == vec3(1, 0, 1) || dis == vec3(1, 0, -1)) skyIndex = 1;
//	else if (dis == vec3(1, 1, 0) || dis == vec3(1, 1, 1) || dis == vec3(1, 1, -1)) skyIndex = 2;
//	else if (dis == vec3(1, -1, 0) || dis == vec3(1, -1, 1) || dis == vec3(1, -1, -1)) skyIndex = 3;
//	else if (dis == vec3(0, 1, 0) || dis == vec3(0, 1, 1) || dis == vec3(0, 1, -1)) skyIndex = 4;
//	else if (dis == vec3(0, -1, 0) || dis == vec3(0, -1, 1) || dis == vec3(0, -1, -1)) skyIndex = 5;
//	//else if (dis == vec3(-1, 0, 0) || dis == vec3(-1, 0, 1) || dis == vec3(-1, 0, -1)) skyIndex = 6;
//	//else if (dis == vec3(-1, 1, 0) || dis == vec3(-1, 1, 1) || dis == vec3(-1, 1, -1)) skyIndex = 7;
//	//else if (dis == vec3(-1, -1, 0) || dis == vec3(-1, -1, 1) || dis == vec3(-1, -1, -1)) skyIndex = 8;
//	else skyIndex = 0;
//
//	if (skyIndex != prevIndex)
//		skyBox[skyIndex].Load();
//}