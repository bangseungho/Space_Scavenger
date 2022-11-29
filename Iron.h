#pragma once
#include "Resource.h"
class Iron : public Resource
{
public:
	static VertexBlock* _Block;

public:
	Iron();
	~Iron();

public:
	void Init();

};