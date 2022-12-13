#include "Player.h"

QuestControl::QuestControl(Player* _Player) : player(_Player)
{
	seccseButton[L"�ۻ��� ����"].name += " Quest �ۻ��� ����";
	seccseButton[L"�ۻ��� ����"].transform.local->position.y = -200;
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

		cout << "����Ʈ ���� : ";
		wcout.imbue(locale("korean"));
		wcout << questName << endl;
		QuestReward(node);
	}
}

void QuestControl::QuestReward(QuestNode* node)
{
	if (node->name == L"�ۻ��� ����")
	{
		player->equipment.find("Harpoon")->second->SetActive(true);
	}
	else if (node->name == L"�ڿ��� �Ѽ�")
	{
		player->equipment.find("LowGun")->second->SetActive(true);
	}
	else if (node->name == L"�ڿ� ���� ��ġ")
	{
		player->equipment.find("Guidance")->second->SetActive(true);
	}
	else if (node->name == L"")
	{

	}
}
