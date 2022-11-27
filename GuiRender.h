#pragma once
#include "GuiObject.h"

class guiRender
{
public:
	static guiRender* gui_objectRender;

public:
	guiRender();
	~guiRender();

public:
	void Draw();
	void AddObject(GuiObject* obj, string layoutName);
	void AddObject(GuiObject* obj) { AddObject(obj, "Default"); };

private:
	map<string, list<GuiObject*>> gui_renderList;
};

