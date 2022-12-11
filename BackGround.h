#pragma once

#include "Render.h"

class BackGround : public Object, public UIMesh
{
public:
	BackGround(string path, string fileName);
	~BackGround();
};