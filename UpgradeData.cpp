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
		UpgradeType* newType = new UpgradeType;
		newType->name = wstring_convert<remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(sheet->readStr(i + 2, 1));
		newType->text = wstring_convert<remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(sheet->readStr(i + 2, 2));
		newType->position = vec3(
			sheet->readNum(i + 2, 3),
			sheet->readNum(i + 2, 4),
			sheet->readNum(i + 2, 5)
		);
		newType->color.SetColor({ 
			(float)sheet->readNum(i + 2, 6),
			(float)sheet->readNum(i + 2, 7),
			(float)sheet->readNum(i + 2, 8),
			(float)sheet->readNum(i + 2, 9) 
			});

		wstring itemsName(sheet->readStr(i + 2, 10));
		itemsName.append(L"\n");
		wstring nums(sheet->readStr(i + 2, 11));
		nums.append(L"\n");
		vector<wstring> nameToken;
		vector<wstring> numToken;

		int endPos = 0;
		int currentPos = 0;

		while ((endPos = itemsName.find(L'\n', currentPos)) != wstring::npos)
		{
			int len = endPos - currentPos;
			nameToken.push_back(itemsName.substr(currentPos, len));
			currentPos = endPos + 1;
		}

		currentPos = 0;
		while ((endPos = nums.find(L'\n', currentPos)) != wstring::npos)
		{
			int len = endPos - currentPos;
			numToken.push_back(nums.substr(currentPos, len));
			currentPos = endPos + 1;
		}

		for (int i = 0; i < nameToken.size(); i++)
		{
			UpgradeData::NeedItem item;
			string str;
			str = wstring_convert<remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(nameToken[i]);

			item.name = str;
			item.count = stoi(numToken[i]);
			newType->needItems.push_back(item);
		}
		type.push_back(newType);
	}
}

UpgradeData::~UpgradeData()
{
	book->release();
}
