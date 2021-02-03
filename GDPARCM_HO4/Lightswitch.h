#pragma once
#include "BusyWaitSemaphore.h"
class Lightswitch
{
	public:
		Lightswitch();
		~Lightswitch();

		void lock();
		void unlock();

	private:
		BusyWaitSemaphore* mutex;
		BusyWaitSemaphore* roomEmpty;
		int counter = 0;
};

