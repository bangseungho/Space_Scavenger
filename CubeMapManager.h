#pragma once

#include "CubeMap.h"

class CubeMapManager : public Object
{
public:
	CubeMapManager(Transform* _Target);
	~CubeMapManager();
	
public:
	//void Update();

public:
	void DrawSky() { skyBox[skyIndex].Draw(); };

private:
	Transform* target_Transform;
	CubeMap skyBox[1] = {
		CubeMap("UI/CubeBox/Default/"),
		//CubeMap("UI/CubeBox/BrightSpace/"),
		//CubeMap("UI/CubeBox/BlueSpace/"),
		//CubeMap("UI/CubeBox/PurpleSpace/"),
		//CubeMap("UI/CubeBox/DarkNavySpace/"),
		//CubeMap("UI/CubeBox/DarkSpace/"),
		//CubeMap("UI/CubeBox/NoStarOrangeSpace/"),
		//CubeMap("UI/CubeBox/NoStarRedSapce/"),
		//CubeMap("UI/CubeBox/OneStarDarkSpace/")
	};	// 왜인지 모르겠지만 6개가 최대치임

	int skyIndex;
	int offset;
};