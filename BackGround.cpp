#include "BackGround.h"

BackGround::BackGround(string path, string flieName) : UIMesh(this)
{
	name = "BackGround";

	Render::uiRender->AddObject(this);
}

BackGround::~BackGround()
{

}