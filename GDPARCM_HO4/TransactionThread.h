#pragma once
#include "IETThread.h"

class SharedBuffer;
class TransactionThread: public IETThread
{
public:
	TransactionThread(int id, SharedBuffer* sharedBuffer, bool isDepositor);
	~TransactionThread();
	
private:
	void run() override;

	SharedBuffer* sharedBuffer;
	bool depositor = true;
	int id = 0;
};

