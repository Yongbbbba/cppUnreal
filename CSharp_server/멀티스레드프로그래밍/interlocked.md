# Interlocked

하드웨어, 컴파일러 최적화 등으로 인해 발생하는 문제들을 해결하기 위한 방안으로 메모리 배리어, volatile 키워드 등이 있었는데, Lock 등의 방법을 사용하면 더 쉽고 우아하게 이 문제들을 해결할 수 있음



## 공유 변수 사용에 의해 발생하는 문제

```c#
using System;
using System.Threading;
using System.Threading.Tasks;

namespace ServerCore
{
    class Program
    {
        static volatile int number = 0;

        static void Thread_1()
        {
            for (int i = 0; i < 100000; i++)
                number++;
        }

        static void Thread_2()
        {
            for (int i = 0; i < 100000; i++)
                number--;
        }
        

        static void Main(string[] args)
        {
            Task t1 = new Task(Thread_1);
            Task t2 = new Task(Thread_2);
            t1.Start();
            t2.Start();

            Task.WaitAll(t1, t2);

            Console.WriteLine(number);
        }
    }
}

```

출력 결과는 0이 아니고 이상한 값이 나온다. 또다시 시작된 멀티스레드의 흑마법.. volatile을 붙여도 소용이 없는 것 봐서는 가시성 문제는 아니다.



## 경합 조건 (race condition)

두 스레드에서 number를 건드리는 부분을 어셈블리 코드로 확인해보면 아래와 같은 형식이다.

```c#
temp = number;
temp += 1;
number = temp;
```

 두 스레드 중에 어떤 것이 먼저 실행될지는 때에 따라 다르다. `number++`가 한 번에 실행되는 것이 아니고  위처럼 단계별로 실행되게 되는데, 만약 number가 0인 상태에서 thread_1이 temp = number를 한 상태에서 thread_2가 number--를 완료해버리면 number는 -1이 된다. 그런데 thread_1이 남은 연산을 마무리하면 number는 -1에 1을 더한 0이 아니라 0에 1을 더한 1이 되어버린다. 즉, 우리가 기대했던 결과가 나오지 않는 것이다. 이는 어떤 동작이 한 번에 실행되어야 한다는 원자성을 위배했기 때문에 발생한 결과이다.

### Interlocked를 활용한 원자성 보장 

Interlocked : 다중 스레드에서 공유하는 변수에 대한 원자 단위 연산을 제공

```c#
using System;
using System.Threading;
using System.Threading.Tasks;

namespace ServerCore
{
    class Program
    {
        static volatile int number = 0;

        static void Thread_1()
        {
            // 연산의 원자성이 보장되어야 한다.

            for (int i = 0; i < 100000; i++)
            {
                Interlocked.Increment(ref number);
            }
        }

        static void Thread_2()
        {
            for (int i = 0; i < 100000; i++)
            {
                Interlocked.Decrement(ref number);
            }
        }
        

        static void Main(string[] args)
        {
            Task t1 = new Task(Thread_1);
            Task t2 = new Task(Thread_2);
            t1.Start();
            t2.Start();

            Task.WaitAll(t1, t2);

            Console.WriteLine(number);
        }
    }
}

```



