#pragma once
#include "Mesh.h"

class Render
{
public:
	static Render* meshtRender;
public:
	Render();
	~Render();

public:
	void Draw();
	void AddObject(Mesh* mesh, string layoutName);
	void AddObject(Mesh* mesh) { AddObject(mesh, "Default"); };

private:
	map<string, list<Mesh*>> renderList;
};

