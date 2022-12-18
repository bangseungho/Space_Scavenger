#include "Player.h"

QuestControl::QuestControl(Player* _Player) : player(_Player)
{
	nowToggle = nullptr;

	for (auto& node : quest.nodeList)
	{
		QuestToggleNode* toggle = new QuestToggleNode;
		toggle->toggle.font.isDraw = false;
		toggle->fontNode.nameFont.text = node.second->name;
		toggle->fontNode.explainFont.text = node.second->explain;
		toggle->fontNode.rewardFont.text = node.second->reward;
		
		toggle->fontNode.OnFont(false);

		questToggles[node.second->name] = toggle;
	}

	int i = 0;
	for (auto& toggle : questToggles)
	{
		toggle.second->toggle.transform.local->position.x = -400;
		toggle.second->toggle.transform.local->position.y = (questToggles.size() / 2.0f - i++) * 100.0f;
	}

	background.color.A = 0.7f;
	successButton.font.text = "Success";
	successButton.transform.local->position.y = -200;

	fontNode.nameFont.lineType = 1;
	fontNode.rewardFont.lineType = 1;

	fontNode.nameFont.transform.local->position.y = 200;
	fontNode.explainFont.transform.local->position.x = -300;
	fontNode.explainFont.transform.local->position.y = 100;
	fontNode.rewardFont.transform.local->position.y = -100;

	isActiveAniamtion = false;
	SetActive(false);
}

QuestControl::~QuestControl()
{
}

void QuestControl::Enable()
{
	background.SetActive(true);
	successButton.SetActive(true);
	for (auto& toggle : questToggles)
		toggle.second->toggle.SetActive(true);

	fontNode.OnFont(true);
}

void QuestControl::Disable()
{
	background.SetActive(false);
	successButton.SetActive(false);
	for (auto& toggle : questToggles)
		toggle.second->toggle.SetActive(false);

	fontNode.OnFont(false);

	//transform.local->position.x = windowSize_W / 2.0f + background.width;
}

void QuestControl::Init()
{
	for (auto& world : transform.world)
	{
		background.transform.world.push_back(world);
		successButton.transform.world.push_back(world);
		for (auto& toggle : questToggles)
			toggle.second->toggle.transform.world.push_back(world);

		fontNode.nameFont.transform.world.push_back(world);
		fontNode.explainFont.transform.world.push_back(world);
		fontNode.rewardFont.transform.world.push_back(world);
	}

	background.transform.world.push_back(transform.local);
	successButton.transform.world.push_back(transform.local);
	for (auto& toggle : questToggles)
		toggle.second->toggle.transform.world.push_back(transform.local);

	fontNode.nameFont.transform.world.push_back(transform.local);
	fontNode.explainFont.transform.world.push_back(transform.local);
	fontNode.rewardFont.transform.world.push_back(transform.local);
}

void QuestControl::Update()
{
	//ActiveAnimation();

	// 현재 고른 Toggle 만 off 할때
	if (nowToggle != nullptr && !nowToggle->toggle.isToggle)
	{
		fontNode.OnFont(false);
		nowToggle = nullptr;
	}

	for (auto& toggle : questToggles)
	{
		if (!toggle.second->toggle.isToggle) continue;
		if (!toggle.second->toggle.ActiveSelf()) continue;
		if (toggle.second == nowToggle) continue;

		if (nowToggle != nullptr)
			nowToggle->toggle.ToggleClick();

		nowToggle = toggle.second;
		fontNode.nameFont.text = nowToggle->fontNode.nameFont.text;
		fontNode.explainFont.text = nowToggle->fontNode.explainFont.text;
		fontNode.rewardFont.text = nowToggle->fontNode.rewardFont.text;
		fontNode.OnFont(true);
	}

	if (!successButton.isClick)
		return;

	for (auto& toggle : questToggles)
	{
		if (!toggle.second->toggle.isToggle)
			continue;
		ClickQuestSeccse(toggle.first);
		return;
	}
}

void QuestControl::ActiveAnimation()
{
	if (isActiveAniamtion)
	{
		SetActive(true);
		transform.local->position.x -= 3000 * FrameTime::oneFrame;
		if (transform.local->position.x < 0)
		{
			transform.local->position.x = 0;
		}
	}
	else
	{
		transform.local->position.x += 3000 * FrameTime::oneFrame;
		if (transform.local->position.x > windowSize_W/2.0f + background.size->width/2)
		{
			SetActive(false);
		}
	}
}

void QuestControl::ClickQuestSeccse(string questName)
{
	PlayerData* pData = PlayerData::Instance;
	if (quest.nodeList.find(questName) != quest.nodeList.cend())
	{
		QuestNode* node = quest.nodeList.find(questName)->second;
		for (auto& item : node->needItems)
		{
			if (pData->resourceCount.find(item.name)->second < item.count)
				return;
		}

		for (auto& item : node->needItems)
		{
			pData->resourceCount.find(item.name)->second -= item.count;
		}

		cout << questName << endl;
		QuestReward(node);
	}
}

void QuestControl::QuestReward(QuestNode* node)
{
	if (node->name == "Let's get a harpoon")
	{
		player->equipment.find("Harpoon")->second->SetActive(true);
	}
	else if (node->name == "Let's shoot a gun")
	{
		player->equipment.find("LowGun")->second->SetActive(true);
	}
	else if (node->name == "resource guidance system")
	{
		player->equipment.find("Guidance")->second->SetActive(true);
	}
	else if (node->name == "")
	{

	}
}
