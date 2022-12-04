#pragma once
#include "Resource.h"
class Iron : public Resource
{
public:
	static VertexBlock* _Block;
	static int amountData;

public:
	Iron();
	~Iron();
};