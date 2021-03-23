#pragma once
#include "IETThread.h"
class MonitorSharedBuffer;
class MonitorTransactionThread :    public IETThread
{
public:
	MonitorTransactionThread(int id, MonitorSharedBuffer* sharedBuffer, bool isDepositor);
	~MonitorTransactionThread();

private:
	void run() override;

	void tryEnter();
	void reportExit();

	MonitorSharedBuffer* sharedBuffer;
	bool depositor = true;
	int id = 0;
};

