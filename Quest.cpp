#include "Quest.h"

libxl::Book* Quest::book = nullptr;
libxl::Sheet* Quest::sheet = nullptr;

QuestNode::QuestNode()
{
	collectCount = 0;
	isSeccse = 0;
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
	}

	int maxCount = sheet->readNum(3, 1);
	for (int i = 0; i < maxCount; i++)
	{
		QuestNode* node = new QuestNode;
		node->name = sheet->readStr(i + 9, 3);
		node->explain = sheet->readStr(i + 9, 4);
		node->reward = sheet->readStr(i + 9, 5);
		node->collectCount = sheet->readNum(i + 9, 6);

		nodeList.push_back(node);
	}
}

Quest::~Quest()
{
}


