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

public:
	Collider collider;

private:
	unsigned int amount;
	vec3 velocity;
};