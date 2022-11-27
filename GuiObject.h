#pragma once

#include "Transform.h"
#include "Color.h"
#include "Camera.h"
class GuiObject
{
public:
	const char* image_file;
	static int Gui_ID_Count;
	static list<GuiObject*> allGuiObject;

	static unsigned int modelLocation;
	static unsigned int vColorLocation;
	unsigned int my_texture;

public:
	GuiObject();
	~GuiObject();

public:
	virtual void Update();
	virtual void Init();
	virtual void ObjectDraw();

public:
	mat4& SetMatrix();

public:
	int id;
	Transform transform;
	Color color;
	string name;

public:


protected:
	unsigned int VBO, VAO, EBO;

};

