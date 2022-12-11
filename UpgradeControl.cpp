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
void UpgradeControl::Update()
{
	if (upgradeButtons.find("Speed")->second.isClick)
	{
		player->speed += 1;
		cout << "Call" << endl;
	}
	else if (upgradeButtons.find("GuidanceDistance")->second.isClick)
	{
		Guidance* guidance = reinterpret_cast<Guidance*>(player->equipment.find("Guidance")->second);
		guidance->serchDistnace *= 1.5f;
	}
}