#pragma once
#include "BusyWaitSemaphore.h"
#include "IETSemaphore.h"


/// <summary>
/// Class that can hold any shared data for demonstration of concurrency
/// </summary>
class SharedBuffer
{
public:
	SharedBuffer();
	~SharedBuffer();

	void depositAmount(int amount);
	void withdrawAmount(int amount);
private:	
	int amount = 0;
	IETSemaphore* withdrawn;
};

