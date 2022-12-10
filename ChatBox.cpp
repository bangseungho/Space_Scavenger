#include "ChatBox.h"

ChatBox::ChatBox() : UIMesh(this)
{
	name = "ChatBox";
	image_file = "chatbox.png";

	// �ʱ� ��ġ, ũ�� ����
	transform.local->scale -= 0.3;
	transform.local->position.x += 0.6;
	transform.local->position.y -= 0.5;
	Render::uiRender->AddObject(this);
}

ChatBox::~ChatBox()
{
}
