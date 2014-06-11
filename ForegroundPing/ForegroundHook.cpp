#include "ForegroundHook.h"

#include <iostream>
#include <sstream>

#define DBOUT( s )            \
{                             \
	std::wostringstream os_;    \
	os_ << s;                   \
	OutputDebugStringW(os_.str().c_str());  \
}

HWND ForegroundHook::_oldWindow;
static int count = 0;
static HWND _switchedWindow = nullptr;
static bool _switching = false;

static void ForegroundChanged(HWND hWnd)
{
	if (_switching) return;
	//HWND fgw = GetForegroundWindow();
	if (ForegroundHook::_oldWindow != NULL && hWnd != ForegroundHook::_oldWindow)
	{
		count++;
		if (count > 30)
			return;
		DBOUT("Changing to foreground");
		SetForegroundWindow(ForegroundHook::_oldWindow);
	}
	else {
		ForegroundHook::_oldWindow = hWnd;
	}
	PlaySound(TEXT("C:\\Windows\\Media\\Speech Misrecognition.wav"), nullptr, SND_FILENAME | SND_ASYNC);
}

static void SwitchChanged(HWND hwnd)
{
	_switching = false;
	ForegroundHook::_oldWindow = hwnd;
	DBOUT("Switch ends");
}

static void SwitchStart(HWND hwnd)
{
	_switching = true;
	DBOUT("Switch start");
	ForegroundHook::_oldWindow = hwnd;
}

void CALLBACK ForegroundHook::WinEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hWnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime)
{
	//if (hWnd && idObject == OBJID_WINDOW && idChild == CHILDID_SELF)
	if (hWnd)
	{
		switch (event)
		{
		case EVENT_SYSTEM_FOREGROUND:
			ForegroundChanged(hWnd);
			break;
		case EVENT_SYSTEM_SWITCHSTART:
			SwitchStart(hWnd);
			break;
		case EVENT_SYSTEM_SWITCHEND:
			SwitchChanged(hWnd);
			break;
		
		}

	}
}

ForegroundHook::ForegroundHook(EventHookHandler handler, MessageHandler messageHandler)
{
	_eventHookHandler = handler;
	_messageHandler = messageHandler;
}


ForegroundHook::~ForegroundHook()
{
}

void ForegroundHook::Run()
{
	_eventHookHandler.RegisterHandler(EVENT_SYSTEM_SWITCHEND);
	_eventHookHandler.RegisterHandler(EVENT_SYSTEM_SWITCHSTART);
	_eventHookHandler.RegisterHandler(EVENT_SYSTEM_FOREGROUND);
	_messageHandler.Run();
	_eventHookHandler.UnregisterAllHandlers();
}

