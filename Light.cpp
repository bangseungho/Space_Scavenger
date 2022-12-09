#include "Light.h"

Shader* Light::lightShader = nullptr;

unsigned int Light::lightPosLocation;
unsigned int Light::lightColorLocation;


unsigned int Light::lightCount;
Light::Light()
{
	light_ID = allLight.size();
	if (lightShader == nullptr)
	{
		
		lightShader = Shader::allProgram.find("Object")->second;
		lightCount = glGetUniformLocation(lightShader->program, "LightCount");
		//lightColorLocation = glGetUniformLocation(lightShader->program, "lightColor");
		//lightPosLocation = glGetUniformLocation(lightShader->program, "lightPos");
	}

	string number = "[" + to_string(light_ID) + "]";
	string posName = "dirLight" + number + ".Pos";
	string colorName = "dirLight" + number + ".Color";

	PosLocation = glGetUniformLocation(lightShader->program, posName.c_str());
	ColorLocation = glGetUniformLocation(lightShader->program, colorName.c_str());


	allLight.push_back(this);
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
	transform.local->scale *= 1;
}

void Light::Update()
{
	float x = transform.local->position.x;
	float y = transform.local->position.y;
	float z = transform.local->position.z;
	//glUniform3f(lightPosLocation, x, y, z); // 임시
	//glUniform3f(lightColorLocation, color.R, color.G, color.B);
	glUniform1i(lightCount, light_ID + 1);
	glUniform3f(PosLocation, x, y, z); // 임시
	glUniform3f(ColorLocation, color.R, color.G, color.B);

	shape.transform = transform;
	shape.color.SetColor(color);
}