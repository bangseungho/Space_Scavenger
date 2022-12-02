#pragma once

#include "Object.h"
#include "Xlsx.h"


class QuestNode : public Object
{
public:
	QuestNode();
	~QuestNode();
public:
	const wchar_t* name;
	const wchar_t* explain;
	const wchar_t* reward;

	int collectCount;

	bool isSeccse;
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
	vector<QuestNode*> nodeList;
};

