#pragma once
#include "IETSemaphore.h"
class Lightswitch
{
	public:
		Lightswitch();
		~Lightswitch();

		void lock();
		void unlock();

	private:
		IETSemaphore* mutex;
		IETSemaphore* roomEmpty;
		int counter = 0;
};

