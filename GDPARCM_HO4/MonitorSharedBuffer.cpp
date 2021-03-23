#include "MonitorSharedBuffer.h"
#include <iostream>

MonitorSharedBuffer::MonitorSharedBuffer()
{
	this->amount = 0;
	this->conditionA = new ConditionClass();
}

MonitorSharedBuffer::~MonitorSharedBuffer()
{
	delete this->conditionA;
}

void MonitorSharedBuffer::depositAmount(int amount)
{
	this->amount += amount;
	std::cout << "[DEPOSIT] My current amount is: " << this->amount << std::endl;
	this->reportDeposit();
}

void MonitorSharedBuffer::withdrawAmount(int amount)
{
	this->tryWithdraw();
	this->amount -= amount;
	std::cout << "[WITHDRAW] My current amount is: " << this->amount << std::endl;
}

void MonitorSharedBuffer::tryWithdraw()
{
	while(this->hasDeposited == false) //guarantees mutual exclusion. see implementation.
	{
		this->conditionA->await();
	}
}

void MonitorSharedBuffer::reportDeposit()
{
	this->hasDeposited = true;
	this->conditionA->notify();
}
