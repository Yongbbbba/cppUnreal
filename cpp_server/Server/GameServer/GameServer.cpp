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
#include "memory.h"

class Knight
{
public:
	Knight()
	{
		cout << "Knight()" << endl;
	}

	Knight(int32 hp) : _hp(hp)
	{
		cout << "Knight(hp)" << endl;
	}

	~Knight()
	{
		cout << "~Knight()" << endl;
	}

	// static 안붙여도 static처럼 동작함 
	//static void* operator new(size_t size)
	//{
	//	cout << "new! " << size << endl;
	//	void* ptr = ::malloc(size);
	//	return ptr;
	//}

	//static void operator delete(void* ptr)
	//{
	//	cout << "delete! " << endl;
	//	::free(ptr);
	//}

	int32 _hp = 100;
	int32  _mp = 50;
};

//  new operator overloading (Global)
// new, delete도 연산자 오버로딩 가능!
//void* operator new(size_t size)
//{
//	cout << "new! " << size << endl;
//	void* ptr = ::malloc(size);
//	return ptr;
//}
//
//void operator delete(void* ptr)
//{
//	cout << "delete!" << endl;
//	::free(ptr);
//}
//
//void* operator new[](size_t size)
//{
//	cout << "new[]! " << size << endl;
//	void* ptr = ::malloc(size);
//	return ptr;
//}
//
//void operator delete[](void* ptr)
//{
//	cout << "delete[]!" << endl;
//	::free(ptr);
//}

int main()
{
	//Knight* knight = new Knight();
	//delete knight;
	// 이런 식으로 메모리 할당과 해제를 하다보면 메모리 단편화 문제가 생겨서, 메모리 풀 같은 것들을 만들어서 메모리 낭비를 막기 위한
	// 프로그래머들의 노력이 있었다. 하지만 컴파일러가 성능이 좋아져서 이렇게 new, delete를 사용해도 잘 관리가 되고 있어서 실제 프로젝트에서 이런 식으로 처리하는 곳이 늘어났다.
	// 하지만 메모리풀을 몰라서 사용 못 하는거랑 알고도 필요가 없어서 안하는거랑은 천지차이이기 때문에 이를 숙지하고 있을 필요가 있다.
	Knight* knight = xnew<Knight>(100);

	xdelete(knight);
	
}
