#pragma once

#include "Shared.h"
#include <vector>


class EventHookHandler
{
public:
	EventHookHandler();
	void RegisterHandler(DWORD event);
	void UnregisterHook(HWINEVENTHOOK hook);
	void UnregisterAllHandlers();
	std::vector<HWINEVENTHOOK> Hooks;
	~EventHookHandler();

private:
	
};

