#pragma once
#include "IETThread.h"
class ServerAcceptingThread :    public IETThread
{
public:
	ServerAcceptingThread();
	~ServerAcceptingThread() = default;

	void serverStart(); //calling this directly is a non-threading call.

protected:
	void run() override;
};

