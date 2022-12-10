#pragma once
#include "Object.h"
#include "Color.h"
#include "OBJ.h"

class Mesh
{
public:
	static list<Mesh*> allMesh;
	static unsigned int vertexLocation;
	static unsigned int uvLoaction;
	static unsigned int normalLocation;

	static unsigned int modelLocation;
	static unsigned int vColorLocation;
		
	static unsigned int KaLocation;	// ���׸��� ���
	static unsigned int KdLocation;	// ���׸��� ���
	static unsigned int KsLocation;	// ���׸��� ���
	static unsigned int dLocation;	// ���׸��� ���

public:
	Mesh(Object* obj);
	~Mesh();

public:
	virtual void MeshInit();
	virtual void Draw();

public:
	OBJ* obj;
	Color color;
	Object* object;

	bool isDraw;

protected:
	GLuint* VAO, *VBO, *EBO;

};

