#pragma once

#include "Shared.h"

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();
	void Run();
private:
	MSG _msg;
};

