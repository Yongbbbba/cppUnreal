#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

// 오늘의 주제 : deque

// deque : double-ended queue 데크
// 실무에서 vector와 list를 많이 쓰지 이건 많이 쓰진 않음
// [    3 3]
// [1 1 1 2]
// [2      ]


int main()
{
	// 시퀀스 컨테이너(Sequence Container)
	// 데이터가 삽입 순서대로 나열되는 형태
	// vector list deque
	
	//deque<int> dq;

	//dq.push_back(1);
	//dq.push_front(2);
	//cout << dq[0] << endl;

	// vector와 마찬가지로 배열 기반으로 동작
	// 다만 메모리 할당 정책이 다르다
	
	vector<int> v(3, 1);
	deque<int> dq(3, 1);
	
	v.push_back(2);
	v.push_back(2);

	dq.push_back(2);
	dq.push_back(2);

	dq.push_front(3);
	dq.push_front(3);

	// - deque의 동작 원리
	// - 중간 삽입/삭제 (BAD / BAD)
	// - 처음/끝 삽입/삭제 (GOOD / GOOD)
	// - 임의 접근 (GOOD),

	dq[3] = 10;
	cout << dq[3] << endl;  // -> 임의 접근 연산이 빠르게 일어나기 때문애 이런 문법이 있는 것.
	// iterator 까보면 몇 동 몇 호를 찾아가는 느낌으로 return을 한다. 그래서 약간 벡터와 비슷하게 바로 랜덤 엑세스가 가능해진다.
	// 임의 접근을 빠르게 해놔서 중간 삽입/삭제가 어렵다.

	return 0;
}