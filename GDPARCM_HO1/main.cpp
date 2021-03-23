#include <iostream>
#include <stdio.h>
#include "HelloWorldThread.h"
#include "IETThread.h"
#include <thread>

void createHWThreads()
{
	for (int i = 0; i < 20; i++)
	{
		HelloWorldThread* thread = new HelloWorldThread(i);
		thread->start();
	}

	//Sleep main thread to avoid premature halting. Wait for other threads to finish execution.
	IETThread::sleep(1000);
}

void testFunctionThread()
{
	std::cout << "Hello world from a thread. " << std::endl;
}

int main() {
	//createHWThreads();
	std::thread myThread(testFunctionThread);
	myThread.join();
}