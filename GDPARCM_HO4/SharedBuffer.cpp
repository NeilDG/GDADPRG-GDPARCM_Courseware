#include "SharedBuffer.h"
#include <iostream>
SharedBuffer::SharedBuffer()
{
	this->amount = 0;
	this->withdrawn = new IETSemaphore(0);
}

SharedBuffer::~SharedBuffer()
{
}

void SharedBuffer::depositAmount(int amount)
{
	this->withdrawn->release();
	this->amount += amount;

	this->withdrawn->acquire();
	std::cout << "[DEPOSIT] My current amount is: " << this->amount << std::endl;
	this->withdrawn->release();
}

void SharedBuffer::withdrawAmount(int amount)
{
	this->withdrawn->acquire();
	this->amount -= amount;
	std::cout << "[WITHDRAW] My current amount is: " << this->amount << std::endl;
}
