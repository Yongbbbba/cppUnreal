#pragma once
#include "Types.h"

/* -------------------------
		RW SpinLock
----------------------------*/

/* -----------------------
* 비트플래그 활용
[WWWWWWWW][WWWWWWWW][RRRRRRRR][RRRRRRRR]  -> 32비트
W : WriteFlag (Exclusive Lock Owner ThreadId)
R : ReadFlag (Shared Lock Count)
--------------------------*/

// 여기서 사용할 Lock 정책
// W -> W (O)
// W -> R (O)
// R -> W (X), 내가 Read를 하고 있을 때 다른 스레드도 read를 하고 있을 수가 있는데, 여기서 내가 write lock을 잡는다는게 문제가 생길 수 있음

class Lock
{
	enum : uint32
	{
		ACQUIRE_TIMEOUT_TICK = 10000,
		MAX_SPIN_COUNT = 5000,
		WRITE_THREAD_MASK = 0xFFFF'0000,
		READ_COUNT_MASK = 0x0000'FFFF,
		EMPTY_FLAG = 0x0000'0000
	};
public:
	void WriteLock(const char* name);
	void WriteUnlock(const char* name);
	void ReadLock(const char* name);
	void ReadUnlock(const char* name);

private:
	Atomic<uint32> _lockFlag = EMPTY_FLAG;
	uint16 _writeCount = 0;

};

/* -----------------------
*			lockGuard
---------------------------*/

class ReadLockGuard
{
public:
	ReadLockGuard(Lock& lock, const char* name) : _lock(lock), _name(name) { _lock.ReadLock(name); }
	~ReadLockGuard() { _lock.ReadUnlock(_name); }
private:
	Lock& _lock;
	const char* _name;
};

class WriteLockGuard
{
public:
	WriteLockGuard(Lock& lock, const char* name) : _lock(lock), _name(name) { _lock.WriteLock(name); }
	~WriteLockGuard() { _lock.WriteUnlock(_name); }
private:
	Lock& _lock;
	const char* _name;

};
