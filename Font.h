#pragma once
#include "Render.h"
class Font : public Object, public Mesh
{
public:
	Font() : Font("Default") {};
	Font(string _Name);
	~Font();

public:
	void MeshInit() {};
	void Draw();
	
public:
	string text;
};