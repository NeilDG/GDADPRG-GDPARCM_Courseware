#include "SharedBuffer.h"
#include <iostream>
SharedBuffer::SharedBuffer()
{
	this->amount = 0;
	this->mutex = new IETSemaphore(1, 1);
	this->withdrawn = new IETSemaphore(0, 1);
}

SharedBuffer::~SharedBuffer()
{
}

void SharedBuffer::depositAmount(int amount)
{
	this->withdrawn->release();
	//this->mutex->acquire();
	this->amount += amount;
	std::cout << "My current amount is: " << this->amount << std::endl;
	//this->mutex->release();
}

void SharedBuffer::withdrawAmount(int amount)
{
	this->withdrawn->acquire();
	//this->mutex->acquire();
	this->amount -= amount;
	std::cout << "My current amount is: " << this->amount << std::endl;
	//this->mutex->release();
}
