#include "Quest.h"

libxl::Book* Quest::book = nullptr;
libxl::Sheet* Quest::sheet = nullptr;

QuestNode::QuestNode()
{
	isSeccse = false;
	SetActive(false);
}

QuestNode::~QuestNode()
{
}

Quest::Quest()
{
	if (book == nullptr)
	{
		book = xlCreateXMLBook();
		book->load(L"Data/QuestData.xlsx");
		sheet = book->getSheet(0);
		if (!sheet)
			cout << "Data/QuestData.xlsx" << " : ������ �ʽ��ϴ�." << endl;
	}

	int maxCount = sheet->readNum(3, 0);
	for (int i = -1; i < maxCount - 1; i++)
	{
		QuestNode* node = new QuestNode;
		node->name = sheet->readStr(i + 9, 2);
		node->explain = sheet->readStr(i + 9, 3);
		node->reward = sheet->readStr(i + 9, 4);

		wstring itemsName(sheet->readStr(i + 9, 5));
		itemsName.append(L"\n");
		wstring nums(sheet->readStr(i + 9, 6));
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
			QuestNode::NeedItem item;
			item.name = nameToken[i];
			item.count = stoi(numToken[i]);
			node->needItems.push_back(item);
		}

		nodeList[node->name] = node;
	}

	SetActive(false);
}

Quest::~Quest()
{
}


