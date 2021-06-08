#include <iostream>
#include "SharedBuffer.h"
#include "TransactionThread.h"
#include <mutex>
#include "MonitorSharedBuffer.h"
#include "MonitorTransactionThread.h"
#include <cstdio>
#include <algorithm>
#include "Lightswitch.h"

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

void runSampleAlgo_Shopaholic()
{
	int T, N, a[20000];

	scanf_s("%d", &T);

	while (T--) {
		scanf_s("%d", &N);

		for (int i = 0; i < N; ++i) scanf_s("%d", &a[i]);
		std::sort(a, a + N);

		int ans = 0;

		for (int i = N - 3; i >= 0; i -= 3)
			ans += a[i];

		printf("%d\n", ans);
	}
}

int main() {
	const int RUNS = 10;
	
	for(int i = 0; i < RUNS; i++)
	{
		std::cout << "Performing run #" << (i + 1) << std::endl;

		runSemaphoreDemo();
		//runMonitorDemo();
		IETThread::sleep(2500);

		std::cout << std::endl;
	}

	//runSampleAlgo_Shopaholic();
	
}