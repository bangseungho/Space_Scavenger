#pragma once
#include "Mesh.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
class UIMesh : public Mesh
{
	static Shader* uiShader;

	static unsigned int ortho_projection;
	static unsigned int texture1_Location;
	// 이 아래 두개 쓰는건가요?
	static unsigned int modelLocation;
	static unsigned int vColorLocation;

public:
	UIMesh(Object* obj);
	~UIMesh();

public:
	void MeshInit();
	void Draw();

public:
	const char* image_file;
	unsigned int my_texture;
};

