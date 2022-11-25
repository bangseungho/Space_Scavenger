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

void Light::Init()
{
	shape.transform.worldScale *= 0.05;
}

void Light::Update()
{
	//float x = transform.worldPosition.x;
	//float y = transform.worldPosition.y;
	//float z = transform.worldPosition.z;
	//glUniform3f(lightPosLocation, x, y, z); // юс╫ц
	//glUniform3f(lightColorLocation, color.R, color.G, color.B);
	shape.transform.worldPosition = transform.worldPosition;
	shape.color.SetColor(color);
}