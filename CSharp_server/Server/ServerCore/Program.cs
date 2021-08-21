using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

// TLS를 사용하면 JobQueue를 사용할 때 Lock을 걸 필요가 없고 그 스레드에 할당된 Task만 처리하면 되니까 효율적이다.

namespace ServerCore
{
    class Program
    {
        static ThreadLocal<string> ThreadName = new ThreadLocal<string>(()=> { return $"My name is {Thread.CurrentThread.ManagedThreadId}"; });

        static void WhoAmI()
        {
            bool repeat = ThreadName.IsValueCreated;
            if (repeat)
                Console.WriteLine(ThreadName.Value + " (repeat)");
            else
                Console.WriteLine(ThreadName.Value);
        }


        static void Main(string[] args)
        {
            ThreadPool.SetMinThreads(1, 1);
            ThreadPool.SetMaxThreads(3,, 3);
            Parallel.Invoke(WhoAmI, WhoAmI, WhoAmI, WhoAmI, WhoAmI, WhoAmI, WhoAmI);
        }
    }
}
