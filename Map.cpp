#include "Map.h"

Map::Map()
{
	name = "Map";
	image_file = "map.png";

	// �ʱ� ��ġ, ũ�� ����
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
