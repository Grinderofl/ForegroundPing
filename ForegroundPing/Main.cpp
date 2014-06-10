#define STRICT

#include "ForegroundHook.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	EventHookHandler handler = EventHookHandler();
	ForegroundHook hook = ForegroundHook(handler);
	
	return 0;
}