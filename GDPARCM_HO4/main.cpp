#include <iostream>
#include "SharedBuffer.h"
#include "TransactionThread.h"
#include <mutex>
void runSemaphoreDemo()
{
	SharedBuffer* buffer = new SharedBuffer();

	TransactionThread* withdrawThread = new TransactionThread(0, buffer, false);
	TransactionThread* depositThread = new TransactionThread(1, buffer, true);

	depositThread->start();
	withdrawThread->start();
	
}
int main() {
	const int RUNS = 5;
	
	for(int i = 0; i < 5; i++)
	{
		std::cout << "Performing run #" << (i + 1) << std::endl;

		runSemaphoreDemo();
		IETThread::sleep(2500);

		std::cout << std::endl;
	}
	
}