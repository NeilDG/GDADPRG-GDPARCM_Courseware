#include "IETSemaphore.h"
#include "IETThread.h"

IETSemaphore::IETSemaphore(int available, int limit)
{
	this->permits = available;
	this->maxPermits = limit;
	this->guard = new Mutex();
}

IETSemaphore::IETSemaphore(int limit)
{
	this->maxPermits = limit;
	this->permits = this->maxPermits;
}

IETSemaphore::~IETSemaphore()
{
}

void IETSemaphore::acquire()
{
	this->guard->lock();
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

void IETSemaphore::release()
{
	this->guard->lock();
	if(this->permits < this->maxPermits)
	{
		this->permits = this->permits + 1;
	}
	this->guard->unlock();
}

void IETSemaphore::wait() const
{
	//no choice but to do busy-waiting.
	while(this->permits == 0)
	{
		IETThread::sleep(1);
	}
}
