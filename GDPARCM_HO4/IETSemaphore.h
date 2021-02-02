#pragma once
#include <mutex>

/// <summary>
/// Representation of a semaphore class
/// </summary>
class IETSemaphore
{
public:
	IETSemaphore(int available, int limit);
	IETSemaphore(int limit);
	~IETSemaphore();

	void acquire();
	void release();

private:
	//typedef std::atomic<int> AtomicInt; //declare permits as atomic operation
	typedef std::mutex Mutex;
	Mutex* guard;
	int permits = 0;
	int maxPermits = 0;
	
	void wait() const; //sleeps the thread and awakes when permits are enough
};

