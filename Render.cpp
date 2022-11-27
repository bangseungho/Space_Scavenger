#include "Render.h"

Render* Render::objectRender = nullptr;

Render::Render()
{
}

Render::~Render()
{
	for (auto& list : renderList)
		list.second.clear();
	renderList.clear();
}

void Render::Draw()
{
	glUseProgram(s_program);

	Camera::mainCamera->Draw();

	for (auto& layer : renderList)
	{
		for (auto& obj : layer.second)
		{
			if (!obj->ActiveSelf())
				continue;

			if (!obj->isDraw)
				continue;

			obj->ObjectDraw();
		}
	}
}

void Render::AddObject(Object* obj, string layoutName)
{
	renderList[layoutName].push_back(obj);
}