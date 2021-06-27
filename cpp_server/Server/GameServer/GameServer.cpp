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
	// 가상 메모리 기본
	
	// 유저 레벨(메모장, 롤, 서버)
	// --------------
	// 커널레벨(OS Code)

	// 2GB [                          ]
	// 운영체제는 보통 페이지 단위로 메모리를 관리한다.
	// 2GB / 4KB[r][w][rw][X][][][][][][][][][]

	SYSTEM_INFO info;
	::GetSystemInfo(&info); 

	info.dwPageSize; // 4kb(0x1000)
	info.dwAllocationGranularity; // 64kb, 메모리할당할 때 이 주소 단위로 반환한다.

	// win api를 사용해서 메모리 할당, 해제하기
	// new, delete 보다 더 정밀함 옵션을 줘서 할당, 해제 가능해진다.
	int* test = (int*)::VirtualAlloc(NULL, 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	*test = 100;
	::VirtualFree(test, 0, MEM_RELEASE);

	*test = 200; // -> delete 했을 때와 다르게 크래쉬가 발생한다. 

	Knight* knight = xnew<Knight>(100);

	xdelete(knight);
	
}
