#pragma once

#include "Mesh.h"

class Collider {
public:
	static list<Collider*> allCollider;
	static VertexBlock* _Block;
	static bool isPrint;

public:
	Collider();
	~Collider();
	
public:
	void Init();
	void DrawBox();

public:
	void SetBox_OBB(const vec3& d);
	void GetBox_OBB();
	bool OBBCollision(const Collider& a,const Collider& b);

public:
	string tag;
	Object* object;

public:
	bool isCollide;
	bool isTrigger;
	bool isMouseCollide;
	bool isWindowCollide;

private:
	Color color;
	vec3 size;

	vec3 axis[3]; // 중심점에서 right, up, front 벡터
	float axisLen[3];
	vec3 defaultAxis[3];

	VertexBlock* block;
	GLuint VAO;
	GLuint VAO_VERTICES;
	GLuint VAO_VERTICES_INDEX;

};