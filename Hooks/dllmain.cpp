// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

HINSTANCE _instance;

#pragma data_seg(".SHARDAT")
static HHOOK _keyboard = nullptr;
static HHOOK _mouse = nullptr;
static HWND _notifyWnd = nullptr;

#pragma data_seg()
#pragma comment(linker, "-section:.SHARDAT,rws")

BOOL APIENTRY DllMain(HINSTANCE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		_instance = hModule;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



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