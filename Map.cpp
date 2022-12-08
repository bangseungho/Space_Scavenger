#include "Map.h"

Map::Map()
{
	name = "Map";
	image_file = "map.png";

	// 초기 위치, 크기 설정
	transform.worldPosition.x -= 0.5;
	transform.worldPosition.y -= 0.7;

}

Map::~Map()
{
}

void Map::Init()
{
	GuiObject::Init();
	guiRender::gui_objectRender->AddObject(this);
}
