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
	void OnDragged(Transform* _Target, float _Speed);	// ������ �ڿ��� ��������

private:
	void Dragged();

public:
	Collider collider;

public:
	bool isDragged;	// �������� �� �ڿ��� ���� ���� �ִ����� ���� üũ

private:
	unsigned int amount;
	vec3 velocity;

	Transform* target;
	float draggedSpeed;

public:
	int level;
};