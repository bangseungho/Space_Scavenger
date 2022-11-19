#pragma once
#include "Object.h"

class Render
{
public:
	Render();
	~Render();

public:
	void Draw();
	void AddObject(Object* obj, string layoutName);
	void AddObject(Object* obj) { AddObject(obj, "Default"); };

public:
	static Render* mainRender;

private:
	map<string, list<Object*>> renderList;
};

