#include "PlayerData.h"

PlayerData* PlayerData::Instance = nullptr;

PlayerData::PlayerData()
{
	if (Instance == nullptr)
		Instance = this;
	book = xlCreateXMLBook();
	book->load(L"Data/PlayerData.xlsx");
	sheet = book->getSheet(0);

	int count = sheet->readNum(1, 0);
	static locale loc("");
	auto& facet = use_facet<codecvt<wchar_t, char, mbstate_t>>(loc);
	for (int i = 0; i < count; i++)
	{
		string type;
		type = wstring_convert<remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(sheet->readStr(i + 5, 2));

		resourceCount[type] = sheet->readNum(i + 5, 3);
	}
}

PlayerData::~PlayerData()
{
	book->release();
}
