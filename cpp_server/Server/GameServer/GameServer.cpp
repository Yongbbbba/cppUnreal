#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <Windows.h>
#include <future>
#include "ThreadManager.h"

#include "SocketUtils.h"
#include "Listener.h"

int main()
{
	Listener listener;
	listener.StartAccept(NetAddress(L"127.0.0.1", 7777));

	for (int32 i = 0; i < 5; i++)
	{
		// 스레드 갯수는 코어 갯수의 1.5배 정도가 적당하다고 알려져있음
		// 너무 늘려봤자 문맥교환 비용만 발생
		GThreadManager->Launch([=]()
		{
			while (true)
			{
				GIocpCore.Dispatch();
			}
		});
	}
	
	GThreadManager->Join();

}
