#pragma once

#include "Vector_AFX.h"

class Transform {
public:
	Transform();
	~Transform();

public:
	void Update();
	void SetScale(); // 랜덤 스케일
	void SetRandomRotate();

	void Info();
	void ReSet();
public:
	void LookAt(float speed);
	void LookAtTarget(const Transform& _Target, const float _Speed);
public:
	vec3 localPosition;
	vec3 localScale;
	vec3 localRotation;
	vec3 localPivot;

	mat4* localModel;
	mat4* worldModel;
	mat4* model;
};