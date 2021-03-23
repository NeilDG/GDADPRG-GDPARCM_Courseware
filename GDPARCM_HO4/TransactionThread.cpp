#include "TransactionThread.h"
#include <iostream>
#include "SharedBuffer.h"
TransactionThread::TransactionThread(int id, SharedBuffer* sharedBuffer, bool isDepositor)
{
	this->id = id;
	this->depositor = isDepositor;
	this->sharedBuffer = sharedBuffer;
}

TransactionThread::~TransactionThread()
{
	delete this->sharedBuffer;
}

void TransactionThread::run()
{
	//critical section start
	if(this->depositor)
	{
		this->sharedBuffer->depositAmount(500);
	}
	else
	{
		this->sharedBuffer->withdrawAmount(500);
	}
}


