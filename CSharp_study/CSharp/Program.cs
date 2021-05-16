using System;
using System.Collections.Generic;

namespace CSharp
{

    class Program
    {

        class Monster
        {
            public int id;
            public Monster(int id) { this.id = id; }
        }
   
        static void Main(string[] args)
        {
            // 딕셔너리

            // 리스트의 단점
            List<int> list = new List<int>();
            // 캐릭터, 몬스터 등에는 ID 식별자를 부여하게 된다.
            // 103이라는 ID를 가진 몬스터를 공격하려고 할 때 그 몬스터를 어떻게 찾을 것인가? 이걸 리스트로 관리하고 있었다면?

            // 특정 Key를 가지고 value에 빠르게 접근하는 방법이 필요
            // Dictionary

            Dictionary<int, Monster> dic = new Dictionary<int, Monster>();

            
            //dic.Add(1, new Monster(1));

            //dic[5] = new Monster(5);

            for (int i=0; i<10000; i++)
            {
                dic.Add(i, new Monster(i));
            }

            Monster mon;
            bool found = dic.TryGetValue(20000, out mon); // 바로 키값을 넣어서 확인하다가 없는 키값을 찾을라고하면 에러가 나기 때문에 TryGetvalue를 활용 

            dic.Remove(7777);
            dic.Clear();

            // Dictionary는 HashTable 기법을 사용
            // 메모리 손해는 있지만 메모리를 내조고, 성능을 취함
            
        }

    }
}

  