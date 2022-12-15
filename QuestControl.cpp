#include "Player.h"

QuestControl::QuestControl(Player* _Player) : player(_Player)
{
	nowToggle = nullptr;

	seccseButton.transform.local->position.y = -200;
	questToggles[L"�ۻ��� ����"] = new Toggle("UI/Toggle/Window/");
	questToggles[L"�ۻ��� ����"]->name += " �ۻ��� ����";
	//questToggles[L"�ۻ��� ����"].transform.local->position.y = -200;

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
