using System;
using System.Collections.Generic;

namespace CSharp
{

     

    class Program
    { 

        class MyList<T> // 조건 부여도 가능  where T : Monster
        {
            T[] arr = new T[10];

            public T GetItem(int i)
            {
                return arr[i];
            }

        }

        class Monster
        {

        }

      
   
        static void Main(string[] args)
        {
            // 제네릭

            MyList<int> myIntList = new MyList<int>();
            int item = myIntList.GetItem(0);
            MyList<short> myShortList = new MyList<short>();
            MyList<Monster> myMonsterList = new MyList<Monster>();
            
        }

    }
}

  