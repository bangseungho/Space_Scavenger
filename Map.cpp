#include "Map.h"

Map::Map()
{
	name = "Map";
	image_file = "map.png";

	// �ʱ� ��ġ, ũ�� ����
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
