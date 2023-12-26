#include "Lightswitch.h"

Lightswitch::Lightswitch()
{
	this->mutex = new IETSemaphore(1);
	this->roomEmpty = new IETSemaphore(1);
}

Lightswitch::~Lightswitch()
{
}

void Lightswitch::lock()
{
	this->mutex->acquire();
	this->counter++;
	if(this->counter == 1)
	{
		this->roomEmpty->acquire(); //get room empty by first thread
	}
	this->mutex->release();
}

void Lightswitch::unlock()
{
	this->mutex->acquire();
	this->counter--;
	if(this->counter == 0)
	{
		this->roomEmpty->release(); //release room empty by last thread
	}
	this->mutex->release();
}
