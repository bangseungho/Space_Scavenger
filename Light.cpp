#include "Light.h"

unsigned int Light::lightPosLocation;
unsigned int Light::lightColorLocation;
unsigned int Light::material;

Light::Light()
{
}

Light::~Light()
{
}

void Light::Enable()
{
	shape.SetActive(true);
}

void Light::Disable()
{
	shape.SetActive(false);
	glUniform3f(lightColorLocation, 0, 0, 0);
}

void Light::Init()
{
	transform.worldScale *= 0.1;
}

void Light::Update()
{
	float x = transform.worldPosition.x;
	float y = transform.worldPosition.y;
	float z = transform.worldPosition.z;
	glUniform3f(lightPosLocation, x, y, z); // �ӽ�
	glUniform3f(lightColorLocation, color.R, color.G, color.B);

	shape.transform = transform;
	shape.color.SetColor(color);
}