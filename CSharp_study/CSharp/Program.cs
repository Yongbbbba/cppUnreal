﻿using System;

namespace CSharp
{
    class Knight
    {
        public int hp;
        public int attack;

        public void Move()
        {
            Console.WriteLine(("Knight move!!");
        }

        public void Attack()
        {
            Console.WriteLine("Knight attack!!");
        }
    }

    class Program
    {

        static void Main(string[] args)
        {
            Knight knight = new Knight();

            knight.hp = 100;
            knight.attack = 10;

            knight.Move();
            knight.Attack();
        }
    }
}
