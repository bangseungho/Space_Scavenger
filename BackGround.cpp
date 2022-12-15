#include "BackGround.h"

BackGround::BackGround(string path, string flieName) : UIMesh(this)
{
	name = "BackGround";
	image_file = path + flieName;

	Render::uiRender->AddObject(this);
}

BackGround::~BackGround()
{

}