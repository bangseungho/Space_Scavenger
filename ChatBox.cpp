#include "ChatBox.h"

ChatBox::ChatBox() : UIMesh(this)
{
	name = "ChatBox";
	image_file = "UI/ChatBox.png";

	count = 0;
	maxChat = 5;
	// 초기 위치, 크기 설정
	transform.local->position.x -= 0.67 * 1600 / 2;
	transform.local->position.y -= 0.68 * 900 / 2;

	for (int i = 0; i < maxChat; i++)
	{
		massage[i].log.transform.local->position.x = -240;
		massage[i].log.transform.local->position.y = -100 + 50 * i;
	}
	Render::uiRender->AddObject(this);
}

ChatBox::~ChatBox()
{
}

void ChatBox::Enable()
{
	for (int i = 0; i < maxChat; i++)
		massage[i].log.SetActive(true);
}

void ChatBox::Disable()
{
	for (int i = 0; i < maxChat; i++)
		massage[i].log.SetActive(false);
}

void ChatBox::Init()
{
	for (const auto& world : transform.world)
	{
		for (int i = 0; i < maxChat; i++)
			massage[i].log.transform.world.push_back(world);
	}
	for (int i = 0; i < maxChat; i++)
		massage[i].log.transform.world.push_back(transform.local);
}

void ChatBox::Update()
{
	for (int i = 0; i < maxChat; i++)
	{
		if (!massage[i].log.ActiveSelf()) continue;
		if (!massage[i].time.CheckTimer()) continue;

		massage[i].log.SetActive(false);
		break;
	}

	while (!DebugManager::Instance->massage.empty())
	{
		int count = 0;
		for (int i = 0; i < maxChat; i++)
		{
			count++;
			if (massage[i].log.ActiveSelf()) continue;

			massage[i].log.SetActive(true);
			massage[i].log.text = DebugManager::Instance->massage.back();
			DebugManager::Instance->massage.pop_back();
			massage[i].time.OnTimer(5);
			break;
		}
		if (count >= maxChat)
		{
			for (int i = 0; i < maxChat; i++)
				massage[i].log.SetActive(false);
			massage[0].log.text = DebugManager::Instance->massage.back();
			DebugManager::Instance->massage.pop_back();
			massage[0].time.OnTimer(5);
		}
	}
}

