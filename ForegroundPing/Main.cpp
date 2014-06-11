#define STRICT

#include "ForegroundHook.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	EventHookHandler handler = EventHookHandler();
	MessageHandler messageHandler = MessageHandler();
	ForegroundHook hook = ForegroundHook(handler, messageHandler);
	hook.Run();
	return 0;
}