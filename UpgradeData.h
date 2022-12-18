#pragma once
#include "Afx.h"
#include "Xlsx.h"
#include "Color.h"

class UpgradeData
{
public:
	static UpgradeData* Instance;
public:
	UpgradeData();
	~UpgradeData();

public:
	libxl::Book* book;
	libxl::Sheet* sheet;

public:
	int maxCount;
	struct NeedItem {
		string name;
		int count;
	};

	struct UpgradeType {
		string name;
		string text;
		vec3 position;
		Color color;
		vector<NeedItem> needItems;
	};

	vector<UpgradeType*> type;
};

