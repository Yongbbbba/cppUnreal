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

        static void Main(string[] args)
        {
            Character choice = Character.None;
            while (choice == Character.None)
            {
                choice = ChooseClass();
                
                Console.WriteLine();
            }
        }
    }
}
