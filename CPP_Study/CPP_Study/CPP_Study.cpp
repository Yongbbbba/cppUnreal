#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
using namespace std;

// 오늘의 주제 : set, multimap, multiset

int main()
{
	// map
	// (Key, Value)
	//map<int, Player*>;

	// 데이터 자체를 key로 사용하고 싶을 때 set 사용
	// map과 문법 거의 흡사
	set<int> s;

	// 넣고
	// 빼고
	// 찾고
	// 순회하고

	// 넣고
	s.insert(10);
	s.insert(30);
	s.insert(20);
	s.insert(40);
	s.insert(50);
	s.insert(70);
	s.insert(90);

	// 빼고
	s.erase(70);

	// 찾고 
	set<int>::iterator findIt = s.find(50);
	if (findIt == s.end())
	{
		cout << "못 찾음" << endl;
	}
	else
	{
		cout << "찾음" << endl;
	}

	//  순회하고
	for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
	{
		cout << (*it) << endl;
	}

	cout << "------------------------------------------" << endl;

	// 키 하나에 값이 여러 개 가능. 실무에서 거의 쓰지 않음. map은 자주 사용. set은 종종 사용
	multimap<int, int> mm;

	// 넣고
	mm.insert(make_pair(1, 100));
	mm.insert(make_pair(1, 200));
	mm.insert(make_pair(1, 300));
	mm.insert(make_pair(2, 400));
	mm.insert(make_pair(2, 500));

	// 빼고
	unsigned int count = mm.erase(1);

	// 찾고

	multimap<int,int>::iterator itFind = mm.find(1);
	if (itFind != mm.end())
	{
		mm.erase(itFind);
	}
	
	pair < multimap<int, int>::iterator, multimap<int, int>::iterator> itPair; // auto itPair
	itPair = mm.equal_range(1);

	for (multimap<int, int>::iterator it = itPair.first; it != itPair.second; ++it)
	{
		cout << it->first << " " << it->second << endl;
	}

	cout << "------------------------------------------" << endl;

	multiset<int> ms;

	// 넣고
	ms.insert(100);
	ms.insert(100);
	ms.insert(100);
	ms.insert(200);
	ms.insert(200);

	// 찾고
	multiset<int>::iterator findIt = ms.find(100);

	

	return 0;
}