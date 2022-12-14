#include "Player.h"

UpgradeControl::UpgradeControl(Player* _Player) : player(_Player)
{
	background.transform.local->scale *= 2;

	upgradeButtons["MaxSpeed"].name += "MaxSpeed";
	upgradeButtons["MaxSpeed"].transform.local->position.x = 200;
	upgradeButtons["MaxSpeed"].color.SetColor({0,0,1,1});
	upgradeButtons["AcceleratSpeed"].name += "AcceleratSpeed";
	upgradeButtons["AcceleratSpeed"].transform.local->position.x = 200;
	upgradeButtons["AcceleratSpeed"].transform.local->position.y = 100;
	upgradeButtons["AcceleratSpeed"].color.SetColor({ 0,0.5,1,1 });
	upgradeButtons["GuidanceDistance"].name += "GuidanceDistance";
	upgradeButtons["GuidanceDistance"].transform.local->position.x = -200;
	upgradeButtons["GuidanceDistance"].color.SetColor({ 1,0,0,1 });

	SetActive(false);
}
UpgradeControl::~UpgradeControl()
{
}
void UpgradeControl::Enable()
{
	for (auto& button : upgradeButtons)
		button.second.SetActive(true);
	background.SetActive(true);
}
void UpgradeControl::Disable()
{
	for (auto& button : upgradeButtons)
		button.second.SetActive(false);
	background.SetActive(false);
}
void UpgradeControl::Update()
{
	if (upgradeButtons.find("MaxSpeed")->second.isClick)
	{
		player->speedBlock.max *= 1.3f;
	}
	else if (upgradeButtons.find("AcceleratSpeed")->second.isClick)
	{
		player->speedBlock.accelerat *= 1.5f;
	}
	else if (upgradeButtons.find("GuidanceDistance")->second.isClick)
	{
		Guidance* guidance = reinterpret_cast<Guidance*>(player->equipment.find("Guidance")->second);
		guidance->serchDistnace *= 1.5f;
	}
}