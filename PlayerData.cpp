#include "PlayerData.h"

PlayerData* PlayerData::Instance = nullptr;

PlayerData::PlayerData()
{
	if (Instance == nullptr)
		Instance = this;
	book = xlCreateXMLBook();
	book->load(L"Data/PlayerData.xlsx");
	sheet = book->getSheet(0);
}

PlayerData::~PlayerData()
{
	book->release();
}
