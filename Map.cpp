#include "Map.h"

Map::Map() : UIMesh(this)
{
	name = "Map";
	image_file = "map.png";

	transform.local->position.x -= 0.67 * 1600/2;
	transform.local->position.y -= 0.68 * 900/2;

	Render::uiRender->AddObject(this);
}

Map::~Map()
{
}