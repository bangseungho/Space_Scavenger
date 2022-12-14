#include "ResourceData.h"

ResourceData* ResourceData::Instance = nullptr;

ResourceData::ResourceData()
{
	if (Instance == nullptr)
		Instance = this;
	book = xlCreateXMLBook();
	book->load(L"Data/ResourceData.xlsx");
	sheet = book->getSheet(0);

	int count = sheet->readNum(1, 0);
	for (int i = 0; i < count; i++)
	{
		resourceTypes.push_back(sheet->readStr(i + 2, 1));
		resourceTexts.push_back(sheet->readStr(i + 2, 2));
	}
}

ResourceData::~ResourceData()
{
	book->release();
}