#pragma once
#include "UIMesh.h"
#include "Camera.h"

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
	void UIDraw();
	void AddObject(Mesh* mesh, string layoutName);
	void AddObject(Mesh* mesh) { AddObject(mesh, "Default"); };
	void RemoveObject(Object* obj);

private:
	map<string, list<Mesh*>> renderList;
};

