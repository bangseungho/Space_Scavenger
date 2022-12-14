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
	vector<wstring> resourceTypes;
	vector<wstring> resourceTexts;
};