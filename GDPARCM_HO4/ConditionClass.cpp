#include "ConditionClass.h"

ConditionClass::ConditionClass()
{
	this->mutex = new Mutex();
	this->lock = new UniqueLock(*this->mutex); 
	this->A = new Condition();
}

ConditionClass::~ConditionClass()
{
	delete this->A;
	delete this->mutex;
	delete this->lock;
}

void ConditionClass::await()
{
	this->A->wait(*this->lock); //ensures mutual exclusion whenever a thread wakes up and needs to check on a condition.
}

void ConditionClass::notify()
{
	this->A->notify_one();
}

void ConditionClass::notifyAll()
{
	this->A->notify_all();
}
