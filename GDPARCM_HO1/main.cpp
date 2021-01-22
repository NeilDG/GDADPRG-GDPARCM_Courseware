#include <iostream>
#include "HelloWorldThread.h"
#include "IETThread.h"

void createHWThreads()
{
	for (int i = 0; i < 20; i++)
	{
		HelloWorldThread* thread = new HelloWorldThread(i);
		thread->start();
	}
	
}
int main() {
	createHWThreads();

	//Sleep main thread to avoid premature halting. Wait for other threads to finish execution.
	IETThread::sleep(1000); 
}