# SpinLock

면접에서도 많이 나옴.. 스핀락 구현해봤냐?



## 잘못된 스핀락 구현

원래 기대값으로는 0이 나와야 하지만 이상한 값이 나온다.

```c#
using System;
using System.Threading;
using System.Threading.Tasks;

namespace ServerCore
{
    class SpinLock
    {
        bool _locked = false;  

        public void Acquire()
        {
            while (_locked)
            {
                // 잠김이 풀리기를 기다린다
                
            }
            _locked = true;  // 내꺼!
        }

        public void Release()
        {
            _locked = false;
        }
    }

    class Program
    {
        static int _num = 0;
        static SpinLock _lock = new SpinLock();

        static void Thread_1()
        {
            for (int i=0; i<100000; i++)
            {
                _lock.Acquire();
                _num++;
                _lock.Release();
            }
        }

        static void Thread_2()
        {
            for (int i = 0; i < 100000; i++)
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

어떤 부분이 틀렸을까? 원자성이 깨지는 경우가 발생하기 떄문이다.

```c#
while (_locked)
{
    
}
_locked = true;
```

이 두 부분이 나눠져 있는데 while문만 실행하고 컨텍스트 스위칭이 발생하면 원자성이 위배된다.

![image-20210517224216404](spinlock.assets/image-20210517224216404.png)

화장실 안에 task 2개가 동시에 들어오는 상황이 발생한다. 

### 해결법 : exchange 사용

```c#
using System;
using System.Threading;
using System.Threading.Tasks;

namespace ServerCore
{
    class SpinLock
    {
        volatile int _locked = 0;  

        public void Acquire()
        {
            while (true)
            {
                int original = Interlocked.Exchange(ref _locked, 1);  // 이전 값을 반환함. 만약 이전 값이 0이라면 내가 잠군 것이 된다.
                if (original == 0) // 이 오리지날은 원본이 아니고 해당 스택 메모리에 존재하는 변수이기 때문에 여기서 비교값으로 사용해도 문제가 전혀 없다.
                    break;
            }
        }

        public void Release()
        {
            _locked = 0;
        }
    }

    class Program
    {
        static int _num = 0;
        static SpinLock _lock = new SpinLock();

        static void Thread_1()
        {
            for (int i=0; i<100000; i++)
            {
                _lock.Acquire();
                _num++;
                _lock.Release();
            }
        }

        static void Thread_2()
        {
            for (int i = 0; i < 100000; i++)
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



```c#
int original = Interlocked.Exchange(ref _locked, 1); 
if (original == 0) //
	break;

// 위 코드를 의사 코드로 표현한다면, 
int original = _locked;
_locked = 1;
if (original == 0)
    break;

// 하지만 위와 같이 코드를 짜면 멀티스레드에서는 원자성이 깨지는 경우가 있기 때문에 Interlocked를 이용하는 것이다.
```



### 해결법 : CompareExchange 사용

Exchange는 무조건 _locked를 바꿔놓고 비교를 하는데 반해 CompareExchange는 comparend를 활용함.

desired => 바뀌기를 바라는 값(잠그기)

expected => 잠금이 풀려있는지 기대하는 값

```c#
using System;
using System.Threading;
using System.Threading.Tasks;

namespace ServerCore
{
    class SpinLock
    {
        volatile int _locked = 0;  

        public void Acquire()
        {
            while (true)
            {
                // CAS (Compare-And-Swap)
                // 의사코드
                //if (_locked == 0)
                //_locked = 1;
                int expected = 0;
                int desired = 1;

               if (Interlocked.CompareExchange(ref _locked, desired, expected) == expected)
                    break;
            }
        }

        public void Release()
        {
            _locked = 0;
        }
    }

    class Program
    {
        static int _num = 0;
        static SpinLock _lock = new SpinLock();

        static void Thread_1()
        {
            for (int i=0; i<100000; i++)
            {
                _lock.Acquire();
                _num++;
                _lock.Release();
            }
        }

        static void Thread_2()
        {
            for (int i = 0; i < 100000; i++)
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

