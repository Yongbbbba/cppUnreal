﻿using System;
using System.Threading;
using System.Threading.Tasks;

namespace ServerCore
{
    class Program
    {
        static volatile int number = 0;
        static object _obj = new object();
        

        static void Thread_1()
        {
            // 연산의 원자성이 보장되어야 한다.

            for (int i = 0; i < 100000; i++)
            {
                Monitor.Enter(_obj); // 문을 잠그는 행위, _obj를 자물쇠라고 생각하자
                number++;
                Monitor.Exit(_obj);  // 잠금을 풀어준다.
            }
        }
         
        static void Thread_2()
        {
            for (int i = 0; i < 100000; i++)
            {
                Monitor.Enter(_obj);
                number--;
                Monitor.Exit(_obj);
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
