#include "Render.h"

Render* Render::objectRender = nullptr;
Render* Render::uiRender = nullptr;
Render* Render::fontRender = nullptr;

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
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	Camera::mainCamera->Draw();
	for (auto& layer : renderList)
	{
		for (auto& mesh : layer.second)
		{
			if (!mesh->isDraw)
				continue;

			if (!mesh->object->ActiveSelf())
				continue;

			mesh->Draw();
		}
	}
}

void Render::UIDraw()
{
	glDisable(GL_DEPTH_TEST);

	for (auto& layer : renderList)
	{
		for (auto& uiMesh : layer.second)
		{
			if (!uiMesh->isDraw)
				continue;

			if (!uiMesh->object->ActiveSelf())
				continue;

			uiMesh->Draw();
		}
	}
}

void Render::FontDraw()
{
	for (auto& layer : renderList)
	{
		for (auto& font : layer.second)
		{
			if (!font->isDraw)
				continue;

			if (!font->object->ActiveSelf())
				continue;

			font->Draw();
		}
	}
}

void Render::SetLayou(string layou[])
{

}

void Render::AddObject(Mesh* mesh, string layoutName)
{
	renderList[layoutName].push_back(mesh);
}

void Render::RemoveObject(Object* obj)
{
	for (auto& layer : renderList)
	{
		for (auto& mesh : layer.second)
		{
			if (mesh->object->id != obj->id)
				continue;

			layer.second.remove(mesh);
			return;
		}
	}
}
