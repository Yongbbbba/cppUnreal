using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace CSharp
{
 
    class Program
    {
        // async/await
        // 이름만 봐도 비동기 프로그래밍! 
        // 게임서버) 비동기 = 멀티스레드 ? ->꼭 그렇지는 않다
        // 유니티) Coroutine = 일종의 비동기 but 싱글스레드

        static Task Test()
        {
            Console.WriteLine("Start Test");
            Task t = Task.Delay(3000);
            return t;
        }

        static async Task TestAsync()
        {
            Console.WriteLine("Start TestAsync");
            await Task.Delay(3000);
            Console.WriteLine("End TestAsync");
        }

        
        static async Task Main(string[] args)
        {
            await TestAsync();

            Console.WriteLine("while start");

            while (true)
            {

            }


        }

    }
}

     