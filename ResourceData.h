#pragma once
#include "Afx.h"
#include "Xlsx.h"

class ResourceData 
{
public:
	static ResourceData* Instance;
public:
	ResourceData();
	~ResourceData();

public:
	libxl::Book* book;
	libxl::Sheet* sheet;

public:
	int maxCount;
	vector<string> resourceTypes;
	vector<string> resourceTexts;
};