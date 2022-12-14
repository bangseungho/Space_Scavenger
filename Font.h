#pragma once
#include "Render.h"
class Font : public Object, public Mesh
{
public:
	static Shader* fontShader;

	static unsigned int ColorLocation;
	static unsigned int PosLocation;
	static unsigned int ortho_projection;
	static unsigned int modelLocation;
public:
	Font() : Font("Font") {};
	Font(string _Name);
	~Font();

public:
	void MeshInit() {};
	void Draw();
	mat4& SetMatrix();
	
public:
	string text;
	int lineType; // 0 : Left, 1 : Middle, 2: Right

private:
	int size;
};