#pragma once
#include "Object.h"

class Render
{
public:
	static Render* objectRender;
	static Render* uiRender;
public:
	Render();
	~Render();

public:
	void Draw();
	void AddObject(Object* obj, string layoutName);
	void AddObject(Object* obj) { AddObject(obj, "Default"); };

private:
	map<string, list<Object*>> renderList;
};

