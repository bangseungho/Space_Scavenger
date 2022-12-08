#include "ChatBox.h"

ChatBox::ChatBox()
{
	name = "ChatBox";
	ReadImage("chatbox.png");
	//image_file = "chatbox.png";

	// 초기 위치, 크기 설정
	transform.localScale -= 0.3;
	transform.localPosition.x += 0.6;
	transform.localPosition.y -= 0.5;

	guiRender::gui_objectRender->AddObject(this);
}

ChatBox::~ChatBox()
{
}