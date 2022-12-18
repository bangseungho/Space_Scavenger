#include "DebugManager.h"

DebugManager* DebugManager::Instance = nullptr;

DebugManager::DebugManager()
{
	if (Instance == nullptr)
		Instance = this;
	else
	{
		delete Instance;
		Instance = this;
	}
}

DebugManager::~DebugManager()
{
	massage.clear();
}

void DebugManager::Log(string _Log)
{
	massage.push_back(_Log);
}
