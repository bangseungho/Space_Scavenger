#pragma once
#include "Resource.h"
class Iron : public Resource
{
public:
	static OBJ* _Obj;
	static int amountData;

public:
	Iron();
	~Iron();
};