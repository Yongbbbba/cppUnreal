using System;
using System.Collections.Generic;

namespace CSharp
{

    class Program
    {

        // 업체 사장 - 사장님의 비서를 통해 연락
        // 우리의 연락처/용건 남겨서 거꾸로 (콜백) 연락을 달라고 .. 

        delegate int OnClicked();  // 함수가 아니라 형식임
        // delegate -> 형식은 형식인데, 함수 자체를 인자로 넘겨주는 그런 형식
        // 반환: int 입력:void
        // Onclicked이 delegate 형식의 이름이다!

        // UI
        static void ButtonPressed(OnClicked clickedFuntion /* 함수 자체를 인자로 넘겨주고 */)
        {
            // PlayAttack();
            // 이렇게 하면 UI 코드와 게임 로직 코드가 엉키게되는 경우가 생길 수 있음. 실제 게임에서 이 부분을 나누는게 중요함

            // 함수를 호출();
            clickedFuntion();
        }

        static int TestDelegate()
        {
            Console.WriteLine("Hello Delegate");
            return 0;
        }
     
        static void Main(string[] args)
        {

            // delegate 대리자
            // 중요하고, 자주 사용되는 문법임

            ButtonPressed(TestDelegate);

        }

    }
}

  