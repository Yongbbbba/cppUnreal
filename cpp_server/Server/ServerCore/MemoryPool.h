#pragma once

/*----------------------
		MemoryHeader
-----------------------*/

// [32] [64] [128] ....
// 다양한 크기의 자료를 담을 수 있는 메모리 풀을 구성한다.
struct MemoryHeader  // 디버깅을 도와주기 위해서
{
	// [MemoryHeader][Data]
	MemoryHeader(int32 size) : allocSize(size) {}

	static void* AttachHeader(MemoryHeader* header, int32 size)
	{
		new(header)MemoryHeader(size); // placement new
		return reinterpret_cast<void*>(++header);
	}

	static MemoryHeader* DetachHeader(void* ptr)
	{
		MemoryHeader* header = reinterpret_cast<MemoryHeader*>(ptr) - 1;
		return header;
	}

	int32 allocSize;
	// TODO: 필요한 추가 정보
};

/*----------------------
		MemoryPool
-----------------------*/

class MemoryPool
{
public:
	MemoryPool(int32 allocSize);
	~MemoryPool();
	
	void Push(MemoryHeader* ptr);
	MemoryHeader* Pop();

private:
	int32 _allocSize = 0;
	atomic<int32> _allocCount = 0;

	USE_LOCK;
	queue<MemoryHeader*> _queue;


};

