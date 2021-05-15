using System;

namespace CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            // 가위바위보 게임 만들기
            // 0:가위 1:바위 2:보
            

            while (true)
            {

                Console.WriteLine("가위바위보!!! (0: 가위 1: 바위 2: 보 // 3: 게임 종료");
                int myChoice = Convert.ToInt32(Console.ReadLine());  // RaadLine은 엔터가 쳐질 때까지 입력을 받음
                Random rand = new Random(DateTime.Now.Millisecond); // 시드 설정
                int aiChoice = rand.Next(0, 3);

                if (myChoice == 0)
                {
                    if (aiChoice == 0)
                        Console.WriteLine("나: 가위 상대: 가위 => 비겼습니다");
                    else if (aiChoice == 1)
                        Console.WriteLine("나: 가위 상대: 바위 => 졌습니다");
                    else
                        Console.WriteLine("나: 가위 상대: 보 => 이겼습니다");
                }
                else if (myChoice == 1)
                {
                    if (aiChoice == 0)
                        Console.WriteLine("나: 바위 상대: 가위 => 이겼습니다");
                    else if (aiChoice == 1)
                        Console.WriteLine("나: 바위 상대: 바위 => 비겼습니다");
                    else
                        Console.WriteLine("나: 바위 상대: 보 => 졌습니다");

                }

                else if (myChoice == 3)
                    break;
                else
                {
                    if (aiChoice == 0)
                        Console.WriteLine("나: 보 상대: 가위 => 졌습니다");
                    else if (aiChoice == 1)
                        Console.WriteLine("나: 보 상대: 바위 => 이겼습니다");
                    else
                        Console.WriteLine("나: 보 상대: 보 => 비겼습니다");
                }
            }
        }
    }
}
