using System;
using System.Collections.Generic;

namespace CSharp
{

    abstract class Monster // 추상 클래스 만들기, 개념적으로만 존재하는... 
    {
        //public virtual void Shout() { }
        public abstract void Shout(); // 추상 클래스를 상속했을 때 그 자식 클래스는 반드시 Shout를 구현해야함. 아니면 에러를 내뱉는다
    }

 

    class Orc : Monster
    {
        public override void Shout()
        {
            Console.WriteLine("록타르 오가르!");
        }
    }

    //abstract class Flyable
    //{
    //    public abstract void Fly();
    //}
    // 다중 상속의 단점 : 죽음의 다이아몬드
    //class FlyableOrc : Orc, Flyable  // c# 에서는 다중 상속이 불가능함, c++에서는 가능
    // 인터페이스는 물려줘도 구현부는 물려주지 않는 방법을 통해 다이아몬드 문제를 해결할 수 있음 => interface라는 문법 사용
    interface IFlyable
    {
        void Fly();
    }
    class FlyableOrc : Orc, IFlyable
    {
        public void Fly()
        {
            Console.WriteLine("나는 날고 있어요");
        }
    }

    static void DoFly(IFlyable flyable)
    {

    }



    class Skeleton : Monster
    {
        public override void Shout()
        {
            Console.WriteLine("꾸에에엑");
        }
    }

    

    class Program
    { 
        static void Main(string[] args)
        {
            // 인터페이스, 추상 클래스

            // Monster monster = new Monster(); // 추상 클래스는 인스턴스를 만들 수 없음 

          
            
        }

    }
}

  