#pragma once

#include "Object.h"

class Collider {
public:
	static ObjectBlock* box_Block;
	static list<Collider*> allCollider;
	static bool isPrint;

public:
	Collider();
	~Collider();
	
public:
	void Init();
	void DrawBox();

public:
	void SetBox(const vec3* box, int size);
	void GetBox();
	bool Collide_XZ(Collider& other);

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

	ObjectBlock block;
	GLuint VAO;
	GLuint VAO_VERTICES, VAO_VERTICES_UVS, VAO_VERTICES_NORMALS;
	GLuint VAO_VERTICES_INDEX, VAO_UV_INDICES, VAO_NORMAL_INDICES;


// 임시 변수
public:
	vec3 rDistance;
private:
	vec3 colliderBox[2];
	vec4 modelbox[2];
};