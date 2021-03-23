#pragma once
#include <mutex>

/// <summary>
/// Representation of a semaphore class through busy waiting
/// </summary>
class BusyWaitSemaphore
{
public:
	BusyWaitSemaphore(int available, int limit);
	BusyWaitSemaphore(int limit);
	~BusyWaitSemaphore();

	void acquire();
	void release();

private:
	typedef std::mutex Mutex;
	Mutex* guard;
	int permits = 0;
	int maxPermits = 0;
	
	void wait() const; //sleeps the thread and awakes when permits are enough
};

