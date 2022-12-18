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
	if (upgradeButtons.find("MaxSpeed")->second->isClick)
	{
		player->speedBlock.max *= 1.3f;
	}
	else if (upgradeButtons.find("AcceleratSpeed")->second->isClick)
	{
		player->speedBlock.accelerat *= 1.5f;
	}
	else if (upgradeButtons.find("GuidanceDistance")->second->isClick)
	{
		Guidance* guidance = reinterpret_cast<Guidance*>(player->equipment.find("Guidance")->second);
		guidance->serchDistnace *= 1.5f;
	}
}

void UpgradeControl::GetData()
{
	data = UpgradeData::Instance;

	for (int i = 0; i < data->maxCount; i++)
	{
		Button* button = new Button;
		button->name += data->name[i];
		button->transform.local->position = data->position[i];
		button->color.SetColor(data->color[i]);
		button->font.text = data->text[i];
		upgradeButtons[data->name[i]] = button;
	}
}
