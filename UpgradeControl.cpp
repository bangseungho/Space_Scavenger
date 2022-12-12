#include "Player.h"

UpgradeControl::UpgradeControl(Player* _Player) : player(_Player)
{
	upgradeButtons["Speed"].name += "Speed";
	upgradeButtons["Speed"].transform.local->position.x = 500;
	upgradeButtons["GuidanceDistance"].name += "GuidanceDistance";
	upgradeButtons["GuidanceDistance"].transform.local->position.x = -500;
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
	if (upgradeButtons.find("Speed")->second.isClick)
	{
		player->speed += 1;
	}
	else if (upgradeButtons.find("GuidanceDistance")->second.isClick)
	{
		Guidance* guidance = reinterpret_cast<Guidance*>(player->equipment.find("Guidance")->second);
		guidance->serchDistnace *= 1.5f;
	}
}