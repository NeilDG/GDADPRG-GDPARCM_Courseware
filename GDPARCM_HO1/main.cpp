#include <iostream>
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
	createHWThreads();

	// std::thread myThread(testFunctionThread);
	// // myThread.join();
	// myThread.detach();
	//
	// std::this_thread::sleep_for(std::chrono::milliseconds(100));
	// std::cout << "My last execution." << std::endl;
	//
	// std::thread* threadPtr = new std::thread(testFunctionThread);
	// threadPtr->join();
}