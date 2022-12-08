#include "ChatBox.h"

ChatBox::ChatBox()
{
	name = "ChatBox";
	image_file = "chatbox.png";

	// 초기 위치, 크기 설정
	transform.local->scale -= 0.3;
	transform.local->position.x += 0.6;
	transform.local->position.y -= 0.5;
}

ChatBox::~ChatBox()
{
}

void ChatBox::Init()
{
	GuiObject::Init();
	guiRender::gui_objectRender->AddObject(this);
}
