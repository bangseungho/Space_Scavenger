#pragma once
#include "Mesh.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
struct ImageSize {
	int width;
	int height;
};

class UIMesh : public Mesh
{
	static Shader* uiShader;

	static unsigned int ortho_projection;
	static unsigned int texture1_Location;
	static unsigned int ColorLocation;
	// �� �Ʒ� �ΰ� ���°ǰ���?
	static unsigned int modelLocation;
	static unsigned int vColorLocation;

public:
	UIMesh(Object* obj);
	~UIMesh();

public:
	void MeshInit();
	void Draw();

public:
	string image_file;
	unsigned int my_texture;

public:
	ImageSize* size;
};

