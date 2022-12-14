#pragma once
#include "UIMesh.h"
#include "Camera.h"

class Render
{
public:
	static Render* objectRender;
	static Render* uiRender;
	static Render* fontRender;
public:
	Render();
	~Render();

public:
	void Draw();
	void UIDraw();
	void FontDraw();
	void SetLayer(string& layer);
	void AddObject(Mesh* mesh, string layoutName);
	void AddObject(Mesh* mesh) { AddObject(mesh, "Default"); };
	void RemoveObject(Mesh* _Mesh);

private:
	map<string, list<Mesh*>> renderList;
};

