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
	GLuint VAO, VBO, EBO;

};

