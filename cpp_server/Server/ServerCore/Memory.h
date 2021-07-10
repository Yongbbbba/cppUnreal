#pragma once
#include "Allocator.h"

class MemoryPool;

/*------------------------
		MemoryManager(메모리풀을 총괄하는 매니저)
--------------------------*/

// pool을 몇 개를 만들어줄거냐는 프로그래머의 선택
class MemoryManager
{
	enum
	{
		// ~1024까지 32단위, ~2048까지 128단위, ~4096까지 256단위
		POOL_COUNT = (1024 / 32) + (1024 / 128) + (2048 / 256),
		MAX_ALLOC_SIZE = 4096
		// 큰 사이즈 같은 경우는 풀링할 필요가 없음
	};
public:
	MemoryManager();
	~MemoryManager();

	void*	Allocate(int32 size);
	void	Release(void* ptr);

private:
	vector<MemoryPool*> _pools;
	// 메모리 크기 <-> 메모리풀
	// O(1) 빠르게 찾기 위한 테이블
	MemoryPool* _poolTable[MAX_ALLOC_SIZE + 1];
};

template<typename Type, typename... Args>
Type* xnew(Args&&... args)
{
	Type* memory = static_cast<Type*>(PoolAllocator::Alloc(sizeof(Type)));

	// placement new
	// rvalue 참조의 경우 move, universal 참조의 경우 forward 사용
	new(memory)Type(std::forward<Args>(args)...);
	return memory;
}

template<typename Type>
void xdelete(Type* obj)
{
	obj->~Type();
	PoolAllocator::Release(obj);
	
}

template<typename Type>
shared_ptr<Type> MakeShared()
{
	return shared_ptr<Type>{xnew<Type>(), xdelete<Type>};
}