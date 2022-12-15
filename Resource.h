#pragma once
#include "Render.h"
#include "Collider.h"
#include "Xlsx.h"
#include "Guidance.h"
#include "Particle.h"

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
	void MoveMent();

public:
	Collider collider;

public:
	int level;
	int amount;

	bool isDragged;	// �������� �� �ڿ��� ���� ���� �ִ����� ���� üũ
private:
	vec3 velocity;

	Transform* target;
	float draggedSpeed;
public:
	//Particle* particles;
};