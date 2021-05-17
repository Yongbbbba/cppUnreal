# ReaderWriterLock

## Lock 개념 복습

1. 근성(SpinLock)
2. 양보
3. 갑질(AutoResetEvent)

셋이 어떤 것이 좋다고는 할 수 없다. 상황에 따라 다르다. 



## Reader-Write-Lock의 개념

Read와 Write는 컴퓨터에서 자원을 사용하는 일반적인 방법이다. 기존의 Mutex 방식 Lock은 같은 자원에 대해서 임계영역을 설정해 그  안에 있으면 Read이건 Write이건 배타적인 사용방식을 고수하였다. 어떤 자원을 한 스레드가 Read하고 있으면 다른 스레드가 Read할 수 없는 식이다. Write도 마찬가지이고.

하지만 보통 단순 읽기 동작은 자원의 일관성을 해치지 않기 때문에 Read 작업에는 Lock을 하지 않으면 자원을 좀 더 효율적으로 사용할 수 있지 않을까라는 아이디어에서 시작한 새로운 자원 관리 방법이 Reader-Write-Lock 개념이다.

## ReaderWriterLock 구현

### 재귀적 락 사용 안하는 경우

```c#
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace ServerCore
{
    // 재귀적 락을 허용할지 (No)
    // 만약 재귀적 락을 허용한다면 : WriteLock -> WriteLock OK, WriteLock->ReadLock OK, ReadLock->WriteLock NO
    // 스핀락 정책 (5000번 -> yield)
    class Lock
    {
        // 비트 플래그 사용
        const int EMPTY_FLAG = 0x00000000;
        const int WRITE_MASK = 0x7FFF0000;
        const int READ_MASK = 0x0000FFFF;
        const int MAX_SPIN_COUNT = 5000;

        // [Unused(1)] [WriteThreadId(15비트)] [ReadCount(16비트)]
        int _flag = EMPTY_FLAG;

        public void WriteLock()
        {
            // 아무도 WriteLock or ReadLock을 획득하고 있지 않을 때, 경합해서 소유권을 얻는다.
            int desired = (Thread.CurrentThread.ManagedThreadId << 16) & WRITE_MASK;
            while (true)
            {
                for (int i=0; i<MAX_SPIN_COUNT; i++)
                {
                    // 시도를 해서 성공하면 리턴
                    if (Interlocked.CompareExchange(ref _flag, desired, EMPTY_FLAG) == EMPTY_FLAG)
                        return ;
                }

                Thread.Yield();
            }
        }

        public void WriteUnlock()
        {
            Interlocked.Exchange(ref _flag, EMPTY_FLAG); // 초기 상태로 바꿔주기
        }

        public void ReadLock()
        {
            // 아무도 WriteLock을 획득하고 있지 않으면, ReadCount를 1 늘린다. 
            while (true)
            {
                for (int i=0; i<MAX_SPIN_COUNT; i++)
                {
                    int expected = (_flag & READ_MASK); 
                    if (Interlocked.CompareExchange(ref _flag, expected+1 ,expected) == expected)
                        return;
                }
                Thread.Yield();
            }
        }
        
        public void ReadUnlock()
        {
            Interlocked.Decrement(ref _flag);
        }
    }
}

```



### 재귀적 락 사용하는 경우

```c#
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace ServerCore
{
    // 재귀적 락을 허용할지 (No)
    // 만약 재귀적 락을 허용한다면 : WriteLock -> WriteLock OK, WriteLock->ReadLock OK, ReadLock->WriteLock NO
    // 스핀락 정책 (5000번 -> yield)
    class Lock
    {
        // 비트 플래그 사용
        const int EMPTY_FLAG = 0x00000000;
        const int WRITE_MASK = 0x7FFF0000;
        const int READ_MASK = 0x0000FFFF;
        const int MAX_SPIN_COUNT = 5000;

        // [Unused(1)] [WriteThreadId(15비트)] [ReadCount(16비트)]
        int _flag = EMPTY_FLAG;
        int _writeCount = 0;

        public void WriteLock()
        {
            // 동일 스레드가 WriteLock을 이미 획득하고 있는지 확인 
            int lockThreadId = (_flag & WRITE_MASK) >> 16;
            if (Thread.CurrentThread.ManagedThreadId == lockThreadId)
            {
                _writeCount++;
                return;
            }

            // 아무도 WriteLock or ReadLock을 획득하고 있지 않을 때, 경합해서 소유권을 얻는다.
            int desired = (Thread.CurrentThread.ManagedThreadId << 16) & WRITE_MASK;
            while (true)
            {
                for (int i=0; i<MAX_SPIN_COUNT; i++)
                {
                    // 시도를 해서 성공하면 리턴
                    if (Interlocked.CompareExchange(ref _flag, desired, EMPTY_FLAG) == EMPTY_FLAG)
                    {
                        _writeCount = 1;
                        return ;

                    }
                }

                Thread.Yield();
            }
        }

        public void WriteUnlock()
        {
            int lockCount = --_writeCount;
            if (lockCount == 0)
                Interlocked.Exchange(ref _flag, EMPTY_FLAG); // 초기 상태로 바꿔주기
        }

        public void ReadLock()
        {
            int lockThreadId = (_flag & WRITE_MASK) >> 16;
            if (Thread.CurrentThread.ManagedThreadId == lockThreadId)
            {
                Interlocked.Increment(ref _flag);
                return;
            }

            // 아무도 WriteLock을 획득하고 있지 않으면, ReadCount를 1 늘린다. 
            while (true)
            {
                for (int i=0; i<MAX_SPIN_COUNT; i++)
                {
                    int expected = (_flag & READ_MASK); 
                    if (Interlocked.CompareExchange(ref _flag, expected+1 ,expected) == expected)
                        return;
                }
                Thread.Yield();
            }
        }
        
        public void ReadUnlock()
        {
            Interlocked.Decrement(ref _flag);
        }
    }
}

```

