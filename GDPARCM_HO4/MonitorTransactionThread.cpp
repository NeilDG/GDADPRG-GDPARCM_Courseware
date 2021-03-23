#include "MonitorTransactionThread.h"
#include "MonitorSharedBuffer.h"
#include "ConditionClass.h"

MonitorTransactionThread::MonitorTransactionThread(int id, MonitorSharedBuffer* sharedBuffer, bool isDepositor)
{
	this->id = id;
	this->depositor = isDepositor;
	this->sharedBuffer = sharedBuffer;
}

MonitorTransactionThread::~MonitorTransactionThread()
{
	delete this->sharedBuffer;
}

void MonitorTransactionThread::run()
{
	//critical section start
	if (this->depositor)
	{
		this->sharedBuffer->depositAmount(500);
	}
	else
	{
		this->sharedBuffer->withdrawAmount(500);
	}
}