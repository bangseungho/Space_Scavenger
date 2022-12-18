#include "Font.h"

Shader* Font::fontShader = nullptr;

unsigned int Font::ColorLocation;
unsigned int Font::PosLocation;
unsigned int Font::ortho_projection;
unsigned int Font::modelLocation;

Font::Font(string _Name) : Mesh(this)
{
	if (fontShader == nullptr)
	{
		fontShader = Shader::allProgram.find("Font")->second;
		ortho_projection = glGetUniformLocation(fontShader->program, "projectionTransform");
		ColorLocation = glGetUniformLocation(fontShader->program, "vColor");
		PosLocation = glGetUniformLocation(fontShader->program, "aPos");
		modelLocation = glGetUniformLocation(fontShader->program, "modelTransform");
	}

	name = "Font";
	text = "";

	size = 24;

	Render::fontRender->AddObject(this, _Name);
}

Font::~Font()
{
	Render::fontRender->RemoveObject(this);
}

void Font::Draw()
{
	int endPos = 0;
	int currentPos = 0;
	string cpyText = text + "\n";
	vector<string> textToken;
	while ((endPos = cpyText.find(L'\n', currentPos)) != wstring::npos)
	{
		int len = endPos - currentPos;
		textToken.push_back(cpyText.substr(currentPos, len));
		currentPos = endPos + 1;
	}

	float tokeSize = textToken.size();
	float y = (tokeSize - 1) * size;

	int i = 0;
	mat4 projection = mat4(1);
	projection = ortho(-windowSize_W / 2, windowSize_W / 2, -windowSize_H / 2, windowSize_H / 2, -1.0, 1.0);
	glUniformMatrix4fv(ortho_projection, 1, GL_FALSE, value_ptr(projection));
	glUniform4f(ColorLocation, color.R, color.G, color.B, color.A);
	for (auto& token : textToken)
	{
		vec2 pos = vec2(0);
		mat4 model = transform.model;

		if (lineType == 1)
			pos.x -= token.size() * size / 4.0f;
		else if (lineType == 2)
			pos.x -= token.size() * size / 4.0f;
		if(tokeSize != 1)
			pos.y += (tokeSize / 2 - i) * y;
		if ((int)y % 2 == 0)
			pos.y -= size / 2.0f;

		model = translate(model, vec3(pos, 0));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

		glRasterPos2f(0, 0);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)token.c_str());
		i++;
	}
}

mat4& Font::SetMatrix()
{
	mat4 localModel = mat4(1.0);
	mat4 worldModel = mat4(1.0);

	for (auto& world : transform.world)
	{
		worldModel = translate(worldModel, world->pivot);
		worldModel = translate(worldModel, world->position);
		worldModel = rotate(worldModel, radians(world->rotation.y), vec3(0, 1.0, 0));
		worldModel = rotate(worldModel, radians(world->rotation.x), vec3(1.0, 0, 0));
		worldModel = rotate(worldModel, radians(world->rotation.z), vec3(0, 0, 1.0));
	}

	localModel = translate(localModel, transform.local->pivot);
	localModel = translate(localModel, transform.local->position);
	localModel = rotate(localModel, radians(transform.local->rotation.y), vec3(0, 1.0, 0));
	localModel = rotate(localModel, radians(transform.local->rotation.x), vec3(1.0, 0, 0));
	localModel = rotate(localModel, radians(transform.local->rotation.z), vec3(0, 0, 1.0));

	transform.localModel = localModel;
	transform.worldModel = worldModel;
	transform.model = worldModel * localModel;

	return transform.model;
}
