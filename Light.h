#pragma once
#include "Color.h"
#include "Transform.h"
#include "Sphere.h"

class Light
{
public:
	static unsigned int lightPosLocation;
	static unsigned int lightColorLocation;
	static unsigned int material;
public:
	Light();
	~Light();

public:
	void Init();
	void Update();

public:
	Color color;
	Transform transform;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	Sphere shape;

public:
	float yRotate = 0;
};

