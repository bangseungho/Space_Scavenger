#include "Map.h"

Map::Map()
{
	name = "Map";
	ReadImage("map.png");
	//image_file = "map.png";

	// 초기 위치, 크기 설정
	transform.localPosition.x -= 0.5;
	transform.localPosition.y -= 0.7;

	guiRender::gui_objectRender->AddObject(this);
}

Map::~Map()
{
}
