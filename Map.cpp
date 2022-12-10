#include "Map.h"

Map::Map()
{
	name = "Map";
	image_file = "map.png";

	// 초기 위치, 크기 설정
	transform.local->position.x -= 0.67;
	transform.local->position.y -= 0.68;
}

Map::~Map()
{
}

void Map::Init()
{
	GuiObject::Init();
	guiRender::gui_objectRender->AddObject(this);
}
