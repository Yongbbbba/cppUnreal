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
