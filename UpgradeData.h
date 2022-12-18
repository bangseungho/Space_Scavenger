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
	vector<string> name;
	vector<string> text;
	vector<vec3> position;
	vector<Color> color;
};

