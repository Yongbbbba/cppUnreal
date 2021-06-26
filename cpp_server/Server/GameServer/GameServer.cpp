#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <Windows.h>
#include <future>
#include "ThreadManager.h"

#include <vector>

// 소수 구하기
bool IsPrime(int number)
{
	if (number <= 1)
		return false;
	if (number == 2 || number == 3)
		return true;

	for (int i = 2; i < number; i++)
	{
		if ((number % i) == 0)
			return false;
	}
	return  true;
}

// [start - end]
int CountPrime(int start, int end)
{
	int count = 0;
	for (int number = start; number <= end; number++)
	{
		if (IsPrime(number))
			count++;
	}
	return count;
}

int main()
{
	const int MAX_NUMBER = 1000'000;

	// 싱글스레드
	// 걸린 시간: 129734
	//const auto beginTime = ::GetTickCount64();
	//int result = CountPrime(2, MAX_NUMBER);
	//const auto endTime = ::GetTickCount64();
	//cout << "걸린 시간 : " << endTime - beginTime << endl;
	//cout << result << endl;

	// 멀티스레드
	const auto beginTime = ::GetTickCount64();
	
	vector<thread> threads;

	int coreCount = thread::hardware_concurrency();
	int jobCount = (MAX_NUMBER / coreCount) + 1;
	
	atomic<int> primeCount = 0;
	for (int i = 0; i < coreCount; i++)
	{
		int start = (i * jobCount) + 1;
		int end = min((i + 1) * jobCount, MAX_NUMBER);
		threads.push_back(thread([start, end, &primeCount]()
		{
			primeCount += CountPrime(start, end);
		}
		));
	}

	for (thread& t : threads)
	{
		t.join();
	}

	const auto endTime = ::GetTickCount64();
	cout << "걸린 시간 : " << endTime - beginTime << endl;
	cout << primeCount << endl;


	
}
