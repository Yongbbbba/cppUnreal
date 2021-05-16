using System;
using System.Collections.Generic;

namespace CSharp
{

    class Program
    { 
        // 객체지향 -> 은닉성
        class Knight
        {
            //protected int hp;

            //public int Hp
            //{
            //    get { return hp; }
            //    set { hp = value; }
            //}

            public int Hp { get; set; } //  아래 코드를 프로퍼티 자동완성을 통해 매우 간단히 작성할 수 있음

            private int _hp;
            public int GetHp() { return _hp; }
            public void SetHp(int value) { _hp = value; }
            
            // Getter Get 함수
            //public int GetHp() { return hp; }
            // Setter Set 함수
            //public void SetHp(int hp) { this.hp = hp; }
        }
        
        static void Main(string[] args)
        {

            // 프로퍼티
            Knight knight = new Knight();
            //knight.hp = 100; 
            //knight.SetHp(100);

            int hp = knight.Hp;
            knight.Hp = 100;

          
            
        }

    }
}

  