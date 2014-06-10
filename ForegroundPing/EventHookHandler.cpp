#include "EventHookHandler.h"
#include "ForegroundHook.h"

EventHookHandler::EventHookHandler()
{
	Hooks = std::vector<HWINEVENTHOOK>();
}


EventHookHandler::~EventHookHandler()
{
}

void EventHookHandler::RegisterHandler(DWORD event)
{
	HWINEVENTHOOK hook = SetWinEventHook(event, event, NULL, ForegroundHook::WinEventProc, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
	Hooks.push_back(hook);
}

void EventHookHandler::UnregisterHook(HWINEVENTHOOK hook)
{
	if (hook)
		UnhookWinEvent(hook);
}

void EventHookHandler::UnregisterAllHandlers()
{
	HWINEVENTHOOK hook;
	while (!Hooks.empty()) 
	{
		hook = Hooks.back();
		UnregisterHook(hook);
		Hooks.pop_back();
	}
}