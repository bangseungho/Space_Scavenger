#include "Image.h"

Image::Image() : UIMesh(this)
{
	name = "Image";
	Render::uiRender->AddObject(this);
}

Image::~Image()
{
}