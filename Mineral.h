#pragma once
#include "Resource.h"
class Mineral : public Resource
{
public:
	static OBJ* _Obj;
	static int amountData;

public:
	Mineral();
	~Mineral();
};

