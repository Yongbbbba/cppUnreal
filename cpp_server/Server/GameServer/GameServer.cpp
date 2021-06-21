#include "pch.h"
#include <iostream>
#include "CorePch.h"

// 원래 os마다 스레드 생성하는 함수가 달랐는데, c++ 11부터 새로운 헤더가 들어와서 작업이 편리해짐.
#include <thread>

void HelloThread()
{
	cout << "Hello Thread" << endl;
}

void HelloThread_2(int32 num)
{
	cout << num << endl;
}

int main()
{
	//cout << "Hello World" << endl;
	// System Call (OS 커널 요청)
	// 고로 출력 작업은 생각보다 부하가 있는 작업이다.
	// 또한 스레드 생성도 시스템 콜을 사용하기 때문에 부하가 있다.
	// 
	// HelloThread();  여기에 이렇게 함수를 실행하면 main 스레드에서 실행되는 것이다.
	/*
	
		std::thread t(HelloThread);  // 스레드의 메인 함수, 즉 엔트리 포인트를 지정해줄 수 있음.
		std::thread t2(HelloThread_2, 10);

		cout << "Hello Main" << endl; 

		int32 count = t.hardware_concurrency();  // cpu 코어 개수가 얼마인지 힌트를 준다. 100프로 확률로 정확하지는 않다. 
		auto id = t.get_id();  // 스레드마다  id가 있음. 스레드 구분을 하고 싶을 때 사용.
		t.detach();  // 스레드 t객체와 실질적으로 구동된 실제 스레드와의 연결고리를 끊어주는 것. 백그라운드 스레드로 독립적으로 동작하게 하는 것. 실제로 쓸 일은 잘 없음
		t.joinable();  // detach 상태라거나 연동된 스레드가 없다거나 하는 것을 판별하기 위해 사용.
		t.join();  // 스레드 t에서 실행한 함수가 끝날 때까지 대기를 하는 것. 이게 끝나기 전에 메인 스레드가 종료되어서는 안되기 때문이다.

		// 흔히 사용하는 용법
		if (t.joinable())
			t.join();
	
	*/

	vector<std::thread> v; 
	for (int32 i = 0; i < 10; i++)
	{
		v.push_back(std::thread(HelloThread_2, i));
	}

	for (int32 i = 0; i < 10; i++)
	{
		if (v[i].joinable())
			v[i].join();
	}

	cout << "Hello Main" << endl;
}
