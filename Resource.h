#pragma once
#include "Render.h"
#include "Collider.h"
#include "Xlsx.h"
#include "Guidance.h"

class Resource : public Object, public Mesh
{
public:
	static libxl::Book* book;
	static libxl::Sheet* sheet;

	static string filePath;
public:
	Resource();
	~Resource();

public:
	virtual void Enable();
	virtual void Disable();
	virtual void Init();
	virtual void Update();
	virtual void OnCollision();

public:
	void OnDragged(Transform* _Target, float _Speed);	// 도구가 자원을 집었을때

private:
	void Dragged();

public:
	Collider collider;

public:
	bool isDragged;	// 누군가가 이 자원을 끓고 가고 있는지에 대해 체크

private:
	unsigned int amount;
	vec3 velocity;

	Transform* target;
	float draggedSpeed;

public:
	int level;
};