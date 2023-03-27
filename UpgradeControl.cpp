#include "Player.h"

UpgradeControl::UpgradeControl(Player* _Player) : player(_Player)
{
	GetData();

	for (auto& button : upgradeButtons)
	{
		button.second->transform.local->scale *= 1.7;
	}

	SetActive(false);
}
UpgradeControl::~UpgradeControl()
{
}
void UpgradeControl::Enable()
{
	for (auto& button : upgradeButtons)
		button.second->SetActive(true);
	background.SetActive(true);
}
void UpgradeControl::Disable()
{
	for (auto& button : upgradeButtons)
		button.second->SetActive(false);
	background.SetActive(false);
}
void UpgradeControl::Update()
{
	PlayerData* pData = PlayerData::Instance;
	int i = -1;
	for (auto& button : upgradeButtons)
	{
		i++;
		if (!button.second->isClick) continue;

		for (auto& item : data->type[i]->needItems)
		{
			if (pData->resourceCount.find(item.name)->second < item.count)
				return;
		}

		for (auto& item : data->type[i]->needItems)
		{
			pData->resourceCount.find(item.name)->second -= item.count;
		}

		ClickUpgrade(button.first);
		break;
	}

}

void UpgradeControl::GetData()
{
	data = UpgradeData::Instance;

	for (int i = 0; i < data->maxCount; i++)
	{
		Button* button = new Button;
		button->name += data->type[i]->name;
		button->transform.local->position = data->type[i]->position;
		button->color.SetColor(data->type[i]->color);
		button->font.text = data->type[i]->text;
		upgradeButtons[data->type[i]->name] = button;
	}
}

// if you want Upgrade Vlaue
// write this
void UpgradeControl::ClickUpgrade(string type)
{
	if (type == "MaxSpeed")
	{
		player->speedBlock.max *= 1.3f;
	}
	else if (type == "AcceleratSpeed")
	{
		player->speedBlock.accelerat *= 1.5f;
	}
	else if (type == "GuidanceDistance")
	{
		Guidance* guidance = reinterpret_cast<Guidance*>(player->equipment.find("Guidance")->second);
		guidance->serchDistnace *= 1.5f;
	}
	else if (type == "Bullet")
	{
		LowGun* lowgun = reinterpret_cast<LowGun*>(player->equipment.find("LowGun")->second);
		lowgun->bulletNum += 2;

		if (lowgun->bulletNum >= 102)
			lowgun->bulletNum += 102;
	}
}
