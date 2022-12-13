#include "Player.h"

QuestControl::QuestControl(Player* _Player) : player(_Player)
{
	seccseButton[L"작살을 얻자"].name += " Quest 작살을 얻자";
	seccseButton[L"작살을 얻자"].transform.local->position.y = -200;
}

QuestControl::~QuestControl()
{
}

void QuestControl::Enable()
{
	for (auto& button : seccseButton)
		button.second.SetActive(true);
}

void QuestControl::Disable()
{
	for (auto& button : seccseButton)
		button.second.SetActive(false);
}

void QuestControl::Update()
{
	for (auto& button : seccseButton)
	{
		if (!button.second.isClick)
			continue;
		ClickQuestSeccse(button.first);
		return;
	}
}

void QuestControl::ClickQuestSeccse(wstring questName)
{
	if (quest.nodeList.find(questName) != quest.nodeList.cend())
	{
		QuestNode* node = quest.nodeList.find(questName)->second;
		for (auto& item : node->needItems)
		{
			if (player->resourceCount.find(item.name)->second < item.count)
				return;
		}

		for (auto& item : node->needItems)
		{
			player->resourceCount.find(item.name)->second -= item.count;
		}

		cout << "퀘스트 성공 : ";
		wcout.imbue(locale("korean"));
		wcout << questName << endl;
		QuestReward(node);
	}
}

void QuestControl::QuestReward(QuestNode* node)
{
	if (node->name == L"작살을 얻자")
	{
		player->equipment.find("Harpoon")->second->SetActive(true);
	}
	else if (node->name == L"자원을 뿌셔")
	{
		player->equipment.find("LowGun")->second->SetActive(true);
	}
	else if (node->name == L"자원 유도 장치")
	{
		player->equipment.find("Guidance")->second->SetActive(true);
	}
	else if (node->name == L"")
	{

	}
}
