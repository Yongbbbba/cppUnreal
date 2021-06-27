#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <Windows.h>
#include <future>
#include "ThreadManager.h"
#include "RefCounting.h"

int main()
{
	// 커스텀한 스마트 포인터의 단점
	// 1) 이미 만들어진 클래스 대상으로 사용 불가
	// 2) 순환 (Cycle) -> 표준 스마트포인터도 마찬가지임

	// unique_ptr
	// shared_ptr
	// weak_ptr

	
	
}
