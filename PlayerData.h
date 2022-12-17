#pragma once
#include "Afx.h"
#include "Xlsx.h"

class PlayerData
{
public:
	static PlayerData* Instance;
public:
	PlayerData();
	~PlayerData();

public:
	libxl::Book* book;
	libxl::Sheet* sheet;

public:
	map<string, int> resourceCount;
};

