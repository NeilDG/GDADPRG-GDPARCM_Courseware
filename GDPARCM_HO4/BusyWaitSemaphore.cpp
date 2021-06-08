#include "BusyWaitSemaphore.h"
#include "IETThread.h"

BusyWaitSemaphore::BusyWaitSemaphore(int available, int limit)
{
	this->permits = available;
	this->maxPermits = limit;
	this->guard = new Mutex();
}

BusyWaitSemaphore::BusyWaitSemaphore(int limit)
{
	this->maxPermits = limit;
	this->permits = this->maxPermits;
}

BusyWaitSemaphore::~BusyWaitSemaphore()
{
}

void BusyWaitSemaphore::acquire()
{
	this->guard->lock(); //ensures atomicity
	if(this->permits > 0)
	{
		this->permits = this->permits - 1; 
		this->guard->unlock();
	}
	else
	{
		this->guard->unlock();
		this->wait();
	}
}

void BusyWaitSemaphore::release()
{
	this->guard->lock();
	if(this->permits < this->maxPermits)
	{
		this->permits = this->permits + 1;
	}
	this->guard->unlock();
}

void BusyWaitSemaphore::wait() const
{
	//no choice but to do busy-waiting.
	while(this->permits == 0)
	{
		IETThread::sleep(1);
	}
}
