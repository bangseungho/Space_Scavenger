#pragma once

#include "Afx.h"
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
	void LookAtTarget(const vec3 targetPos);
public:
	vec3 worldPosition;
	vec3 localPosition;

	vec3 worldScale;
	vec3 localScale;

	vec3 worldRotation;
	vec3 localRotation;

	vec3 worldPivot;
	vec3 localPivot;

	mat4 model;
};