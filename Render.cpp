#include "Render.h"

Render* Render::mainRender = nullptr;

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
			if (!obj->isActive)
				continue;

			obj->ObjcetDraw();
		}
	}
}

void Render::AddObject(Object* obj, string layoutName)
{
	renderList[layoutName].push_back(obj);
}