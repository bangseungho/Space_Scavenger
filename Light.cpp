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
	}

	string number = "[" + to_string(light_ID) + "]";
	string posName = "dirLight" + number + ".Pos";
	string colorName = "dirLight" + number + ".Color";

	PosLocation = glGetUniformLocation(lightShader->program, posName.c_str());
	ColorLocation = glGetUniformLocation(lightShader->program, colorName.c_str());

	glUseProgram(lightShader->program);
	glUniform1i(lightCount, light_ID + 1);

	isDraw = false;

	allLight.push_back(this);
}

Light::~Light()
{
}

void Light::Enable()
{
	//shape.SetActive(true);
}

void Light::Disable()
{
	//shape.SetActive(false);
	glUniform3f(lightColorLocation, 0, 0, 0);
}

void Light::Init()
{
}

void Light::Update()
{
	vec3 pos = vec3(0);
	for (const auto& world : transform.world)
		pos += world->position;
	pos += transform.local->position;
	
	glUniform3f(PosLocation, pos.x, pos.y, pos.z); // юс╫ц
	glUniform3f(ColorLocation, color.R, color.G, color.B);

	//shape.transform = transform;
	//shape.color.SetColor(color);
}