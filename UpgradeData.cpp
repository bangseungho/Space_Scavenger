#include "UpgradeData.h"

UpgradeData* UpgradeData::Instance = nullptr;

UpgradeData::UpgradeData()
{
	if (Instance == nullptr)
		Instance = this;
	book = xlCreateXMLBook();
	book->load(L"Data/UpgradeData.xlsx");
	sheet = book->getSheet(0);

	maxCount = sheet->readNum(1, 0);
	static locale loc("");
	auto& facet = use_facet<codecvt<wchar_t, char, mbstate_t>>(loc);
	for (int i = 0; i < maxCount; i++)
	{
		string str;
		vec3 pos;
		Color c;
		str = wstring_convert<remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(sheet->readStr(i + 2, 1));
		name.push_back(str);
		str = wstring_convert<remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(sheet->readStr(i + 2, 2));
		text.push_back(str);
		pos = vec3(
			sheet->readNum(i + 2, 3),
			sheet->readNum(i + 2, 4),
			sheet->readNum(i + 2, 5)
		);
		position.push_back(pos);
		c.SetColor({ 
			(float)sheet->readNum(i + 2, 6),
			(float)sheet->readNum(i + 2, 7),
			(float)sheet->readNum(i + 2, 8),
			(float)sheet->readNum(i + 2, 9) 
			});
		color.push_back(c);
	}
}

UpgradeData::~UpgradeData()
{
	book->release();
}
