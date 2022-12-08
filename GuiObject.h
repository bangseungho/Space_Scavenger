#pragma once
#include "Transform.h"
#include "Color.h"
#include "Camera.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
class GuiObject
{
public:
	static int Gui_ID_Count;
	static list<GuiObject*> allGuiObject;

	static unsigned int ortho_projection;
	static unsigned int texture1_Location;
	// 이 아래 두개 쓰는건가요?
	static unsigned int modelLocation;
	static unsigned int vColorLocation;
public:
	GuiObject();
	~GuiObject();

public:
	virtual void Enable() {};
	virtual void Disable() {};
	virtual void Update();
	virtual void Init();
	virtual void ObjectDraw();
	virtual mat4& SetMatrix();

public:
	bool ActiveSelf() { return isActive; };
	void SetActive(bool value);

public:
	int id;
	Transform transform;
	Color color;
	string name;

public:
	const char* image_file;
	unsigned int my_texture;

protected:
	unsigned int VBO, VAO, EBO;

private:
	bool isActive;

};

