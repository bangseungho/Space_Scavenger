#include "ChatBox.h"

ChatBox::ChatBox()
{
	name = "ChatBox";
	ReadImage("chatbox.png");
	//image_file = "chatbox.png";

	// �ʱ� ��ġ, ũ�� ����
	transform.localScale -= 0.3;
	transform.localPosition.x += 0.6;
	transform.localPosition.y -= 0.5;

	guiRender::gui_objectRender->AddObject(this);
}

ChatBox::~ChatBox()
{
}