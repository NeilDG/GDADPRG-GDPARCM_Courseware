#pragma once
#include <condition_variable>
/// <summary>
/// Class holding a condition variable.
/// </summary>
class ConditionClass
{
	public:
		ConditionClass();
		~ConditionClass();

		void await();
		void notify();
		void notifyAll();

	private:
		typedef std::condition_variable Condition;
		typedef std::mutex Mutex;
		typedef std::unique_lock<Mutex> UniqueLock;

		Mutex* mutex;
		UniqueLock* lock;
		Condition* A;
	
};

