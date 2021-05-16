using System;

namespace CSharp
{
    // ref
   
    

    class Program
    {
        static int GetHighestScore(int[] scores)
        {
            int result = scores[0];

            foreach (var score in  scores)
            {
                if (score > result) result = score;    
            }
            return result;
        }

        static int GetAverageScore(int[] scores)
        {
            if (scores.Length == 0) return 0;
            int result = 0;
            int len = scores.Length;
            
            foreach(var score in scores)
            {
                result += score;
            }

            return result / len;
           
        }

        static int GetIndexOf(int[] scores, int value)
        {
            int len = scores.Length;
            if (len == 0) return -1;

            int result = -1;

            for (int i = 0; i < len; i++)
            {
                if (value == scores[i])
                {
                    result = i;
                    break;
                }
            }
            return result;
        }
      
        static void Main(string[] args)
        {
            // 배열
            int[] scores = new int[5] { 10, 30, 40, 20, 50 };
            int average = GetAverageScore(scores);
            int maxV = GetHighestScore(scores);
            int where = GetIndexOf(scores, 30);

            Console.WriteLine($"{average},  {maxV}");
            Console.WriteLine(where);
        }

    }
}

