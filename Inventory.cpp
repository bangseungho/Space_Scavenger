#include "Player.h"

Inventory::Inventory(Player* _Player) : player(_Player)
{
	name = "Inventory";

	GetData();

	SetActive(false);
}

Inventory::~Inventory()
{
}

void Inventory::Enable()
{
	background.SetActive(true);
	for (int i = 0; i < rData->maxCount; i++)
	{
		resourceSlot[i]->amountFont.text = to_string(pData->resourceCount.find(rData->resourceTypes[i])->second);
		resourceSlot[i]->SetActive(true);
	}
}

void Inventory::Disable()
{
	background.SetActive(false);
	for (auto& rSlot : resourceSlot)
	{
		rSlot->SetActive(false);
	}
}

void Inventory::Init()
{
	for (auto& world : transform.world)
	{
		background.transform.world.push_back(world);
		for (auto& rSlot : resourceSlot)
			rSlot->transform.world.push_back(world);
	}
	background.transform.world.push_back(transform.local);
	for (auto& rSlot : resourceSlot)
		rSlot->transform.world.push_back(transform.local);
}

void Inventory::GetData()
{
	pData = PlayerData::Instance;
	rData = ResourceData::Instance;
	for (int i = 0; i < rData->maxCount; i++)
	{
		ResourceSlot* rSlot = new ResourceSlot;
		rSlot->image.image_file = "UI/Resource/" + rData->resourceTypes[i] + ".png";
		rSlot->amountFont.text = to_string(pData->resourceCount.find(rData->resourceTypes[i])->second);

		rSlot->transform.local->position.x = -400;
		rSlot->transform.local->position.y = 200 + i * -70;
		resourceSlot.push_back(rSlot);
	}
}


void Inventory::ResourceSlot::Enable()
{
	image.SetActive(true);
	amountFont.SetActive(true);
}

void Inventory::ResourceSlot::Disable()
{
	image.SetActive(false);
	amountFont.SetActive(false);
}

void Inventory::ResourceSlot::Init()
{
	amountFont.transform.local->position.x = 70;

	for (auto& world : transform.world)
	{
		image.transform.world.push_back(world);
		amountFont.transform.world.push_back(world);
	}
	image.transform.world.push_back(transform.local);
	amountFont.transform.world.push_back(transform.local);
}