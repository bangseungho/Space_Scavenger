#pragma once

#include "Transform.h"
#include "Color.h"
#include "Camera.h"
class GuiObject
{
public:
	static int Gui_ID_Count;
	static list<GuiObject*> allGuiObject;

	static unsigned int ortho_projection;
	static unsigned int texture1_Location;
	// �� �Ʒ� �ΰ� ���°ǰ���?
	static unsigned int modelLocation;
	static unsigned int vColorLocation;
public:
	GuiObject();
	~GuiObject();
	void ReadImage(string _FileName);

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
	bool isDraw;

public:
	string image_file;
	unsigned int my_texture;

private:
	bool isActive;

protected:
	unsigned int VBO, VAO, EBO;
};

