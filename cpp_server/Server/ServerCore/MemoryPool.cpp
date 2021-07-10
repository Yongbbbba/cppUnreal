#include "pch.h"
#include "MemoryPool.h"

MemoryPool::MemoryPool(int32 allocSize) : _allocSize(allocSize)
{

}

MemoryPool::~MemoryPool()
{
	while (_queue.empty() == false)
	{
		// 꺼내서 해제
		MemoryHeader* header = _queue.front();
		_queue.pop();
		::free(header);
	}
}

void MemoryPool::Push(MemoryHeader* ptr)
{
	// 데이터 필요없어지면 pool에 반납
	WRITE_LOCK;
	ptr->allocSize = 0;

	_queue.push(ptr);
	_allocCount.fetch_sub(1);
	
}

MemoryHeader* MemoryPool::Pop()
{
	MemoryHeader* header = nullptr;
	{
		WRITE_LOCK;
		//pool에 여분 데이터가 있는지 확인
		if (_queue.empty() == false)
		{
			// 있으면 하나 꺼내온다
			header = _queue.front();
			_queue.pop();
		}
	}

	// 없으면 새로 데이터 할당
	if (header == nullptr)
	{
		header = reinterpret_cast<MemoryHeader*>(::malloc(_allocSize));
	}
	else
	{
		ASSERT_CRASH(header->allocSize == 0);
	}

	_allocCount.fetch_add(1);  // atomic 변수임

	return nullptr;
}

