#pragma once

#include "Transform.h"
#include "Color.h"
#include "Camera.h"
#include "MouseControl.h"

class Object {
public:
	static int ID_Count;
	static list<Object*> allObject;

	static unsigned char key;
	static int specialKey;

	static unsigned int modelLocation;
	static unsigned int vColorLocation;
	static unsigned int objectColorLocation;

public:
	Object();
	~Object();

public:
	virtual void Enable() {};
	virtual void Disable() {};
	virtual void Update();
	virtual void Init();
	virtual void ObjectDraw();
	virtual void Collision();

	//virtual void Handle_Evnet();

public:
	bool ActiveSelf() { return isActive; };
	void SetActive(bool value);
	void Info();
public:
	mat4& SetMatrix();

public:
	int id;
	string name;
	Transform transform;
	Color color;
	bool isDraw = true;

	ObjectBlock* block;
public:
	vec3 worldSpeed;
	vec3 localSpeed;

	vec3 worldPivotSpeed;

	vec3 worldRotateSpeed;
	vec3 localRotateSpeed;

protected:
	GLuint VAO;
	GLuint VAO_VERTICES, VAO_VERTICES_UVS, VAO_VERTICES_NORMALS;
	GLuint VAO_VERTICES_INDEX, VAO_UV_INDICES, VAO_NORMAL_INDICES;

private:
	bool isActive;
	
};