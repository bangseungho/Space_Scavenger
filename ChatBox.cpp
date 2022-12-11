#include "ChatBox.h"

ChatBox::ChatBox() : UIMesh(this)
{
	name = "ChatBox";
	image_file = "chatbox.png";

	// 초기 위치, 크기 설정
	transform.local->position.x += 0.7 * 1600/2;
	transform.local->position.y -= 0.5 * 900/2;
	Render::uiRender->AddObject(this);
}

ChatBox::~ChatBox()
{
}
