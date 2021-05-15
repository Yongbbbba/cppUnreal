using System;

namespace CSharp
{
    class Program
    {
        enum Character
        {
            None = 0,
            Knight=1,
            Archer,
            Mage
        }

        struct Player
        {
            public int hp;
            public int attack;
        }

        static Character ChooseClass()
        {
            Character choice = Character.None;
            Console.WriteLine("직업을 선택하세요!");
            Console.WriteLine("[1]기사\n[2]궁수\n[3]법사");
            int input;
            input = Convert.ToInt32(Console.ReadLine());

            if (input == 1)
            {
                choice = Character.Knight;
            }
            else if (input == 2)
            {
                choice = Character.Archer;
            }
            else if (input == 3)
            {
                choice = Character.Mage;
            }

            
            return choice;
        }

        static void CreatePlayer(Character choice, out Player player)
        {
            if (choice == Character.Knight)
            {
                player.attack = 25;
                player.hp = 100;
            }
            else if (choice == Character.Archer)
            {
                player.attack = 35;
                player.hp = 70;
            }
            else
            {
                player.attack = 50;
                player.hp = 50;
            }
          
        }

        static void Main(string[] args)
        {
            while (true)
            {
                Character choice = ChooseClass();
                if (choice != Character.None)
                {
                    // 캐릭터 생성
                    Player player;
                    CreatePlayer(choice, out player);
                    break;
                }
                
                Console.WriteLine();
            }
        }
    }
}
