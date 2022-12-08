#include "guiRender.h"

guiRender* guiRender::gui_objectRender = nullptr;

guiRender::guiRender()
{
}

guiRender::~guiRender()
{
	for (auto& list : gui_renderList)
		list.second.clear();
	gui_renderList.clear();
}

void guiRender::Draw()
{
	glDisable(GL_DEPTH_TEST);

	for (auto& layer : gui_renderList)
	{
		for (auto& ui : layer.second)
		{
			if (!ui->ActiveSelf())
				continue;
			ui->ObjectDraw();
		}
	}
}

void guiRender::AddObject(GuiObject* obj, string layoutName)
{
	gui_renderList[layoutName].push_back(obj);
}