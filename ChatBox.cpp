#include "ChatBox.h"

ChatBox::ChatBox()
{
	name = "ChatBox";
	image_file = "chatbox.png";

	// �ʱ� ��ġ, ũ�� ����
	transform.localScale -= 0.3;
	transform.worldPosition.x += 0.6;
	transform.worldPosition.y -= 0.5;
}

ChatBox::~ChatBox()
{
}

void ChatBox::Init()
{
	GuiObject::Init();
	guiRender::gui_objectRender->AddObject(this);
}
