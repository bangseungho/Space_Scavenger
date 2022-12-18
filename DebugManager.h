#pragma once
#include "Afx.h"

class DebugManager
{
public:
	static DebugManager* Instance;

public:
	DebugManager();
	~DebugManager();

public:
	void Log(string _Log);

public:
	list<string> massage;
};

