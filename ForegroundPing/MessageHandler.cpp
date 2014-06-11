#include "MessageHandler.h"


MessageHandler::MessageHandler()
{
}


MessageHandler::~MessageHandler()
{
}

void MessageHandler::Run()
{
	while (GetMessage(&_msg, nullptr, 0, 0))
	{
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
	}
}