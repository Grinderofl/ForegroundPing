// Hooks.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Hooks.h"

#pragma data_seg(".SHARDAT")
static HHOOK _keyboard = nullptr;
static HHOOK _mouse = nullptr;
static HWND _notifyWnd = nullptr;

#pragma data_seg()
#pragma comment(linker, "-section:.SHARDAT,rws")

extern HINSTANCE _instance;

UINT keyPressID = ::RegisterWindowMessage(L"WM_GLOBAL_KEYPRESS");
UINT mouseID = ::RegisterWindowMessage(L"WM_GLOBAL_MOUSE");

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION && _notifyWnd)
		SendMessage(_notifyWnd, keyPressID, wParam, lParam);

	return CallNextHookEx(_keyboard, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION && _notifyWnd)
		SendMessage(_notifyWnd, mouseID, wParam, lParam);

	return CallNextHookEx(_mouse, nCode, wParam, lParam);
}

extern "C" {

	HOOKS_API bool _cdecl Install(HWND notify)
	{
		if (!_instance) return false;
		_notifyWnd = notify;
		_keyboard = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, _instance, 0);
		_mouse = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseProc, _instance, 0);
		return (bool)_keyboard && (bool)_mouse;
	}

	HOOKS_API bool _cdecl Uninstall()
	{
		return UnhookWindowsHookEx(_keyboard) && UnhookWindowsHookEx(_mouse);
	}
}