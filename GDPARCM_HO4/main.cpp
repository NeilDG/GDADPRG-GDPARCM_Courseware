#include <iostream>
#include "SharedBuffer.h"
#include "TransactionThread.h"
#include <mutex>
#include "MonitorSharedBuffer.h"
#include "MonitorTransactionThread.h"
void runSemaphoreDemo()
{
	SharedBuffer* buffer = new SharedBuffer();

	TransactionThread* withdrawThread = new TransactionThread(0, buffer, false);
	TransactionThread* depositThread = new TransactionThread(1, buffer, true);

	depositThread->start();
	withdrawThread->start();
	
}

void runMonitorDemo()
{
	MonitorSharedBuffer* buffer = new MonitorSharedBuffer();

	MonitorTransactionThread* withdrawThread = new MonitorTransactionThread(0, buffer, false);
	MonitorTransactionThread* depositThread = new MonitorTransactionThread(1, buffer, true);

	depositThread->start();
	withdrawThread->start();
}

int main() {
	const int RUNS = 10;
	
	for(int i = 0; i < RUNS; i++)
	{
		std::cout << "Performing run #" << (i + 1) << std::endl;

		//runSemaphoreDemo();
		runMonitorDemo();
		IETThread::sleep(2500);

		std::cout << std::endl;
	}
	
}