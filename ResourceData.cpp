#include "ResourceData.h"

ResourceData* ResourceData::Instance = nullptr;

ResourceData::ResourceData()
{
	if (Instance == nullptr)
		Instance = this;
	book = xlCreateXMLBook();
	book->load(L"Data/ResourceData.xlsx");
	sheet = book->getSheet(0);

	maxCount = sheet->readNum(1, 0);

	static locale loc("");
	auto& facet = use_facet<codecvt<wchar_t, char, mbstate_t>>(loc);

	for (int i = 0; i < maxCount; i++)
	{
		string str;
		str = wstring_convert<remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(sheet->readStr(i + 2, 1));
		resourceTypes.push_back(str);
		str = wstring_convert<remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(sheet->readStr(i + 2, 2));
		resourceTexts.push_back(str);
	}
}

ResourceData::~ResourceData()
{
	book->release();
}