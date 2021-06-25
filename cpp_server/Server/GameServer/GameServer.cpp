#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <Windows.h>
#include <future>
#include "ConcurrentQueue.h"
#include "ConcurrentStack.h"

//queue<int32> q;  // 게임만들 때 스택보다 큐를 정말 많이 쓴다. 먼저 도착한 패킷을 먼저 처리해주는 것이 일반적이기 때문에.
//stack<int32> s;
LockQueue<int32> q;
LockStack<int32> s;

void Push()
{
	while (true)
	{
		int32 value = rand() % 100;
		q.Push(value);

		this_thread::sleep_for(10ms);
	}
}

void Pop()
{
	while (true)
	{
		int32 data = 0;
		if (q.TryPop(data))
			cout << data << endl;
		
	}
}

int main()
{
	thread t1(Push);
	thread t2(Pop);

	t1.join();
	t2.join();
	
}
