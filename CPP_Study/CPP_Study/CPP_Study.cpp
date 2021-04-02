#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
using namespace std;

// 오늘의 주제 : 연습 문제

int main()
{
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
		for (auto& num : v)
		{
			if (num == number)
			{
				found = true;
				break;
			}
		}
		for (it = v.begin(); it != v.end(); ++it)
		{
			if ((*it) == number)
				break;
		}
		cout << "1번 답 : found = " << found << endl;

		if (it == v.end())
		{
			cout << "찾지 못 했습니다" << endl;
		}
		else
		{
			cout << "1번 답 : it = " << *it << endl;
		}
		int a = 3;
	}

	// Q2) 11로 나뉘는 숫자가 벡터에 있는지 체크하는 기능 (bool, 첫 등장 iterator)
	{
		bool found = false;
		vector<int>::iterator it;

		// TODO
		for (auto& num : v)
		{
			if (num % 11 == 0)
			{
				found = true;
				break;
			}
		}
		for (it = v.begin(); it != v.end(); ++it)
		{
			if ((*it) % 11 == 0)
				break;
		}

		
		cout << "2번 답 : found = " << found << endl;

		if (it == v.end())
		{
			cout << "찾지 못 했습니다" << endl;
		}
		else
		{
			cout << "2번 답 : it = " << *it << endl;
		}
		
	}
	
	// Q3) 홀수인 숫자의 개수는? (count)
	{
		int count = 0;

		// TODO
		for (auto& num : v)
		{
			if (num % 2)
				count++;
		}
		cout << "3번 답 : count = " << count << endl;
	}

	// Q4) 벡터에 들어가 있는 모든 숫자들에 3을 곱해주세요!
	{
		for (auto& num : v)
			num *= 3;

		for (auto num : v)
			cout << num << endl;
	}



	return 0;
}