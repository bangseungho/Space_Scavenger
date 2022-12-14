#include "Player.h"

QuestControl::QuestControl(Player* _Player) : player(_Player)
{
	nowToggle = nullptr;

	seccseButton.transform.local->position.y = -200;
	questToggles[L"작살을 얻자"] = new Toggle("UI/Toggle/Window/");
	questToggles[L"작살을 얻자"]->name += " 작살을 얻자";
	//questToggles[L"작살을 얻자"].transform.local->position.y = -200;

	SetActive(false);
}

QuestControl::~QuestControl()
{
}

void QuestControl::Enable()
{
	seccseButton.SetActive(true);
	for (auto& toggle : questToggles)
		toggle.second->SetActive(true);
}

void QuestControl::Disable()
{
	seccseButton.SetActive(false);
	for (auto& toggle : questToggles)
		toggle.second->SetActive(false);
}

void QuestControl::Update()
{
	for (auto& toggle : questToggles)
	{
		if (!toggle.second->ActiveSelf())
			continue;

		if (toggle.second == nowToggle)
			continue;

		if (nowToggle != nullptr)
			nowToggle->ToggleClick();

		nowToggle = toggle.second;
	}

	if (!seccseButton.isClick)
		return;

	for (auto& toggle : questToggles)
	{
		if (!toggle.second->isToggle)
			continue;
		ClickQuestSeccse(toggle.first);
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
