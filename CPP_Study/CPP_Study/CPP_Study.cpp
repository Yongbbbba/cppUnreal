#include <iostream>
#include <vector>
#include <list>

using namespace std;

// 오늘의 주제 : list
// vector는 동적 방식, list는 node 방식

// vector : 동적 배열
// [      ]
// [                   ]  필요하면 용량 증설

// [ data(4)   next( data(4) next(    )  .... ] 
// 문법적으로 말이 안되는 표현
//class Node2
//{
//public:
//	Node2 _next;
//	int _data;
//};

// [ data(4) next(4or8) ]
class Node
{
public:
public:
	Node* _next;
	int _data;
	Node* _prev;
};

// 단일 / 이중 / 원형
// list : 연결 리스트

// [1]    ->   [2]  -> [3]      -> [4]    ->  [5]    -> 연속된 공간에 배치되지는 않음



int main()
{	
	// list (연결 리스트)
	// - list의 동작 원리
	// - 중간 삽입/삭제 (GOOD / GOOD)
	// - 처음/끝 삽입/삭제 ( GOOD / GOOD )
	// - 임의 접근 (i번째 데이터는 어디 있습니까?) BAD, 임의 접근 연산자 자체가 없음 그래서.

	list<int> li;

	for (int i=0; i< 100; i++)
		li.push_back(i);

	//li.push_front(10);
	int size = li.size();
	//li.capacity(); // 없음
	
	int first = li.front();
	int last = li.back();

	//li[3] = 10; // 없음

	list<int>::iterator itBegin = li.begin();
	list<int>::iterator itEnd = li.end();

	int* ptrBegin = &(li.front());
	int* ptrEnd = &(li.back());

	for (list<int>::iterator it = li.begin(); it != li.end(); ++it)
	{
		cout << *it << endl;
	}

	//li.insert(itBegin, 100);

	//li.erase(li.begin());

	//li.pop_front();

	//li.remove(10); // 10의 값과 동일한 데이터를 모두 삭제, vector의 경우 중간 값을 삭제하는 것이 매우 비효율적이기 때문에 vector에는 이런게 없음

	// * 임의 접근이 안 된다
	// * 그런데 중간 삽입/삭제 빠르다? 

	// 50번 인덱스에 있는 데이터를 삭제!
	list<int>::iterator it = li.begin();
	for (int i = 0; i < 50; i++)
		++it;
	// 리스트의 삭제가 빠르다는 것은 탐색/삭제 둘을 분리해서 봤을 때 그렇다는 것이다.벡터는 위치를 알아도 삭제 작업 자체가 느리니깐.
	li.erase(it);


	return 0;
}