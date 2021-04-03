#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// 오늘의 주제 : 연습 문제

int main()
{
	// 자료구조 (데이터를 저장하는 구조)
	// 알고리즘 (데이터를 어떻게 사용할 것인가?)

	// find
	// find_if
	// count
	// count_if
	// all_of
	// any_of
	// none_of
	// for_each
	// 
	// remove
	// remove_if


	srand(static_cast<unsigned int>(time(nullptr)));
	vector<int> v;

	for (int i = 0; i < 100; i++)
	{
		int num = rand() % 100;
		v.push_back(num);
	}

	// Q1) number라는 숫자가 벡터에 있는지 체크하는 기능 (bool, 첫 등장 iterator)
	{
		int number = 50;

		bool found = false;
		vector<int>::iterator it;

		// TODO
		vector<int>::iterator itFind = find(v.begin(), v.end(), number);
		if (itFind == v.end())
		{
			// 못찾았음
			cout << "못 찾음" << endl;
		}
		else
		{
			cout << "찾았음" << endl;
		}
	}

	// Q2) 11로 나뉘는 숫자가 벡터에 있는지 체크하는 기능 (bool, 첫 등장 iterator)
	{
		bool found = false;
		vector<int>::iterator it;

		// TODO
		// 함수 객체 활용
		struct CanDivideBy11
		{
			bool operator() (int n)
			{
				return (n % 11) == 0;
			}
		};

		auto itFind = find_if(v.begin(), v.end(), CanDivideBy11());  // 람다식을 사용하면 더 간단하게 할 수 있음
		if (itFind == v.end())
		{
			// 못찾았음
			cout << "못 찾음" << endl;
		}
		else
		{
			cout << "찾았음" << endl;
		}
	}
	
	// Q3) 홀수인 숫자의 개수는? (count)
	{
		struct IsOdd
		{
			bool operator() (int n)
			{
				return (n % 2) != 0;
			}
		};
		int n = count_if(v.begin(), v.end(), IsOdd());
		cout << "총 : " << n << "개" << endl;

		// 모든 데이터가 홀수 입니까>
		bool b1 = all_of(v.begin(), v.end(), IsOdd());
		//홀수인 데이터가 하나라도 있습니까?
		bool b2 = any_of(v.begin(), v.end(), IsOdd());
		// 모든 데이터가 홀수가 아닙니까?
		bool b3 = none_of(v.begin(), v.end(), IsOdd());
	}

	// Q4) 벡터에 들어가 있는 모든 숫자들에 3을 곱해주세요!
	{
		struct MultiplyBy3
		{
			void operator()(int& n)
			{
				n = n * 3;
			}
		};

		for_each(v.begin(), v.end(), MultiplyBy3());
	}

	// 홀수인 데이터를 일괄 삭제
	{
		for (vector<int>::iterator it = v.begin(); it != v.end();)
		{
			if (*it % 2 != 0)
				it = v.erase(it);
			else
				++it;
		}
		v.clear();
		v.push_back(1);
		v.push_back(4);
		v.push_back(3);
		v.push_back(5);
		v.push_back(8);
		v.push_back(2);

		struct IsOdd
		{
			bool operator() (int n)
			{
				return (n % 2) != 0;
			}
		};


		// 1 4 3 5 8 2
		// 4 8 2 5 8 2 
		//remove(v.begin(), v.end(), 4);

		vector<int>::iterator it = remove_if(v.begin(), v.end(), IsOdd());
		// remove_if는 삭제가 이뤄지는게 아니고, 홀수가 아닌 값을 앞쪽으로 move시킨다.
		// 그래서 4 8 2 5 8 2라는 묘한 값으로 벡터가 변해있고, 반환되는 이터레이터 이후부터는 5 8 2 값이 들어가는 것이다
		// 그래서 아래와 같이 그 이터레이터 이후의 값을 제거해줘야 원하는 벡터의 값들을 얻을 수 있게 된다.
		v.erase(it, v.end());
	}

	return 0;
}