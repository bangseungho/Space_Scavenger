#pragma once
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
};

