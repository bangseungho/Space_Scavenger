#pragma once

#include "Vector_AFX.h"

class TransformBlock {
public:
	TransformBlock();
	~TransformBlock();

public:
	void ReSet();

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
	void SetScale(); // 랜덤 스케일
	void SetRandomRotate();
	void CurrentFront();
	void LookAt(float speed);
	void LookAtTarget(const Transform& _Target, const float _Speed);
	void RotateAtTarget(const Transform& _Target, const float _Speed);
	void Info();

public:
	vector<TransformBlock*> world;
	TransformBlock* local;

	mat4 worldModel;
	mat4 localModel;
	mat4 model;

	vec3 front;
};