#pragma once

#include "Vector_AFX.h"

class TransformBlock {
public:
	TransformBlock();
	~TransformBlock();

public:
	vec3 pivot;
	vec3 position;
	vec3 rotation;
	vec3 scale;
};

class Transform {
public:
	Transform();
	~Transform();
public:
	void Update();

public:
	void SetScale(); // ���� ������
	void SetRandomRotate();
	void LookAt(float speed);
	void LookAtTarget(const Transform& _Target, const float _Speed);
	void Info();
public:
	vector<TransformBlock*> world;
	TransformBlock* local;

	mat4 worldModel;
	mat4 localModel;
	mat4 model;
};