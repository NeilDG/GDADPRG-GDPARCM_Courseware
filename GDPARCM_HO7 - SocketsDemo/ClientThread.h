#pragma once
#include "IETThread.h"
class ClientThread :    public IETThread
{
public:
	ClientThread();
	~ClientThread() = default;

	void clientStart(); //calling this directly is a non-threading call.

protected:
	void run() override;
};

