# Auto Reset Event

식당에서 화장실을 갔는데 똥칸이 모두 다 차있을 때, 다른 사람(커널)에게 똥칸이 비어있는지 계속 감시를 시키는 일.



## AutoResetEvent

```c#
using System;
using System.Threading;
using System.Threading.Tasks;

namespace ServerCore
{
    class SpinLock
    {
        // boolean 값인데, 커널에서 관리하는 값이라고 생각하면 됨
        AutoResetEvent _available = new AutoResetEvent(true);

        public void Acquire()
        {
            _available.WaitOne();  // 입장 시도, 문을 닫는 작업을 자동으로 해줌. (_available = false)
        }

        public void Release()
        {
            _available.Set();  // boolean 값을 다시 true로 바꿔줌
        }
    }

    class Program
    {
        static int _num = 0;
        static SpinLock _lock = new SpinLock();

        static void Thread_1()
        {
            for (int i=0; i<10000; i++)
            {
                _lock.Acquire();
                _num++;
                _lock.Release();
            }
        }

        static void Thread_2()
        {
            for (int i = 0; i < 10000; i++)
            {
                _lock.Acquire();
                _num--;
                _lock.Release();
            }

        }
        
        static void Main(string[] args)
        {
            Task t1 = new Task(Thread_1);
            Task t2 = new Task(Thread_2);

            t1.Start();
            t2.Start();

            Task.WaitAll(t1, t2);

            Console.WriteLine(_num);

        }
    }
}

```

속도가 스핀락보다 오래 걸린다.



