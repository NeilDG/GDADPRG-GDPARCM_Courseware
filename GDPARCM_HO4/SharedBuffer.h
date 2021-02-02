#pragma once
#include "IETSemaphore.h"
#include <semaphore>


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
	typedef std::binary_semaphore BinarySemaphore;
	
	int amount = 0;
	IETSemaphore* withdrawn;
	BinarySemaphore* withdrawSem;
};

