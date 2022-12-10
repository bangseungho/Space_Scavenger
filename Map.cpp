#include "Map.h"

Map::Map() : UIMesh(this)
{
	name = "Map";
	image_file = "map.png";

	// 초기 위치, 크기 설정
	transform.local->position.x -= 0.5;
	transform.local->position.y -= 0.7;

	Render::uiRender->AddObject(this);
}

Map::~Map()
{
}