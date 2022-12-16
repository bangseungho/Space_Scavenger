#pragma once
#include "Mesh.h"

class Collider {
public:
	//static list<Collider*> allCollider;
	static vector<Collider*> allCollider;
	static list<Collider*> initCollider;
	static OBJ* _Obj;
	static bool isPrint;

	static bool OBBCollision(Collider& a,Collider& b);
public:
	Collider();
	~Collider();
	
public:
	void Init();
	void DrawBox();

public:
	void SetBox_OBB(const vec3& d);
	void GetBox_OBB();

public:
	string tag;
	Object* object;
	Color color;

public:
	bool isCollide;

private:
	vec3 size;

	vec3 axis[3]; // 중심점에서 right, up, front 벡터
	float axisLen[3];
	vec3 defaultAxis[3];

	OBJ* obj;
	GLuint VAO;
	GLuint VAO_VERTICES;
	GLuint VAO_VERTICES_INDEX;
};