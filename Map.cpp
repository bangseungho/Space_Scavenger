#include "Map.h"

Map::Map() : UIMesh(this)
{
	name = "Map";
	image_file = "map.png";

	// �ʱ� ��ġ, ũ�� ����
	transform.local->position.x -= 0.5;
	transform.local->position.y -= 0.7;

	Render::uiRender->AddObject(this);
}

Map::~Map()
{
}