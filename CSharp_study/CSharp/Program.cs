using System;

namespace CSharp
{
    // ref
    class Knight
    {
        public int hp;
        public int attack;

        // c++의 복사생성자 같이 기능하는듯.
        // deep copy 방법
        public Knight Clone()
        {
            Knight knight = new Knight();
            knight.hp = hp;
            knight.attack = attack;

            return knight;
        }
        public void Move()
        {
            Console.WriteLine("Knight move!!");
        }

        public void Attack()
        {
            Console.WriteLine("Knight attack!!");
        }
    }

    // 복사
    struct Mage
    {
        public int hp;
        public int attack;

    }

    

    class Program
    {
        static void KillMage(Mage mage)
        {
            mage.hp = 0;
        }

        static void KillKnight(Knight knight)
        {
            knight.hp = 0;
        }
        static void Main(string[] args)
        {
            Mage mage;
            Knight knight = new Knight();

            mage.hp = 50;
            mage.attack = 20;

            knight.hp = 100;
            knight.attack = 10;

            KillKnight(knight);
            KillMage(mage);

            Console.WriteLine(mage.hp);
            Console.WriteLine(knight.hp);

            // 얕은 복사
            Knight knight2 = knight;
            knight2.hp = 1000; // knight1의 값도 같이 바뀜 => 얕은 복사

            // 깊은 복사
            Knight knight3 = new Knight();
            knight3.hp = knight.hp;
            knight3.attack = knight.attack;

            Knight knight4 = knight.Clone();
            knight4.hp = 5000;
            knight4.attack = 1;
            
            
        }

    }
}
