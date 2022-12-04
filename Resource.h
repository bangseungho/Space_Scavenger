#pragma once
#include "Object.h"
#include "Render.h"
#include "Collider.h"
#include "Xlsx.h"

class Resource : public Object, public Mesh
{
public:
	static libxl::Book* book;
	static libxl::Sheet* sheet;
public:
	Resource();
	~Resource();

public:
	virtual void Init();
	virtual void Update();
	virtual void OnCollision();

public:
	void OnDragged(Transform* _Target);	// ������ �ڿ��� ��������

private:
	void Dragged();

public:
	Collider collider;

private:
	unsigned int amount;
	vec3 velocity;

	Transform* target;
	bool isDragged;
};