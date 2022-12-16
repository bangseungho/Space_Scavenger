#pragma once

#include "Object.h"
#include "Xlsx.h"


class QuestNode : public Object
{
public:
	QuestNode();
	~QuestNode();
public:
	bool isSeccse;
	string name;
	string explain;
	string reward;

	struct NeedItem {
		string name;
		int count;
	};

	vector<NeedItem> needItems;
};

class Quest : public Object
{
public:
	static libxl::Book* book;
	static libxl::Sheet* sheet;
public:
	Quest();
	~Quest();

public:
	map<string, QuestNode*> nodeList;
};

