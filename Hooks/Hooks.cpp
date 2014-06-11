// Hooks.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Hooks.h"

#pragma data_seg(".SHARDAT")
static HHOOK _keyboard = nullptr;
static HWND _notifyWnd = nullptr;
UINT keyPressID = ::RegisterWindowMessage(L"WM_GLOBAL_KEYPRESS");
#pragma data_seg()
#pragma comment(linker, "-section:.SHARDAT,rws")

extern HINSTANCE _instance;

LRESULT __declspec(dllexport)__stdcall CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION && _notifyWnd)
		SendMessage(_notifyWnd, keyPressID, wParam, lParam);

	return CallNextHookEx(_keyboard, nCode, wParam, lParam);
}


// This is an example of an exported variable
HOOKS_API int nHooks=0;

// This is an example of an exported function.
HOOKS_API int fnHooks(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see Hooks.h for the class definition
CHooks::CHooks()
{
	return;
}

bool CHooks::Install(HWND notify)
{
	if (!_instance) return false;
	_notifyWnd = notify;
	_keyboard = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, _instance, 0);
	return (bool)_keyboard;
}

bool CHooks::Uninstall()
{
	return UnhookWindowsHookEx(_keyboard);
}