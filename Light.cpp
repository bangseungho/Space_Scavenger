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
	transform.local->scale *= 0.1;
}

void Light::Update()
{
	float x = transform.local->position.x;
	float y = transform.local->position.y;
	float z = transform.local->position.z;
	glUniform3f(lightPosLocation, x, y, z); // юс╫ц
	glUniform3f(lightColorLocation, color.R, color.G, color.B);

	shape.transform = transform;
	shape.color.SetColor(color);
}