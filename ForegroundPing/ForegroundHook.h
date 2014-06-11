#pragma once
#pragma comment( lib, "Winmm.lib" )

#include "Shared.h"
#include "EventHookHandler.h"
#include "MessageHandler.h"
#include <mmsystem.h>

class ForegroundHook
{
public:
	HWINEVENTHOOK hWinEventHook;
	ForegroundHook(EventHookHandler handler, MessageHandler messageHandler);
	~ForegroundHook();
	void Run();
	static HWND _oldWindow;
	static void CALLBACK WinEventProc(HWINEVENTHOOK, DWORD, HWND, LONG, LONG, DWORD, DWORD);

private:
	EventHookHandler _eventHookHandler;
	MessageHandler _messageHandler;
};

