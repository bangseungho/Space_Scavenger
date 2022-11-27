#pragma once
#include "Object.h"
#include "Color.h"

class Mesh
{
public:
	static list<Mesh*> allMesh;
	static unsigned int modelLocation;
	static unsigned int vColorLocation;

public:
	Mesh(Object* obj);
	~Mesh();

public:
	void MeshInit();
	void Draw();

public:
	Color color;
	Object* object;

	bool isDraw;

	VertexBlock* block;

protected:
	GLuint VAO;
	GLuint VAO_VERTICES, VAO_VERTICES_UVS, VAO_VERTICES_NORMALS;
	GLuint VAO_VERTICES_INDEX, VAO_UV_INDICES, VAO_NORMAL_INDICES;
	GLuint UBO_MATERIAL_BLOCK;

};

