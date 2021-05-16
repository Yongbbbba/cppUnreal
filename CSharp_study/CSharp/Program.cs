using System;
using System.Collections.Generic;

namespace CSharp
{

    class Program
    {
    
      
        static void Main(string[] args)
        {
            // List <- 동적 배열
            List<int> list = new List<int>();
            
            for (int i=0; i<5; i++)
            {
                list.Add(i);
            }

            // 삽입 삭제
            list.Insert(2, 999); // 2번 인덱스에 999를 넣어주세요
         
            list.RemoveAt(0); // 해당 인덱스의 값을 지우는 것
            list.Remove(999);  // 값을 지우는 것. 여러 개 있으면 처음 만나는 애를 삭제 함 (얘는 O(N)의 복잡도를 가짐. 앞에서부터 탐색을 해야하니까)

            list.Clear();  // 전체 삭제
          

        }

    }
}

  