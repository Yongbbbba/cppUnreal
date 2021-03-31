#include <iostream>
#include <vector>

using namespace std;

// 오늘의 주제 : vector




int main()
{	
	// 컨테이너(Container) : 데이터를 저장하는 객체 (자료구조 Data Structure, 데이터를 어떤 식을 저장할 것인가?) 

	// vector (동적 배열)
	// - vector의 동작 원리 (size/capacity)
	// - 중간 삽입/ 삭제 
	// - 처음/끝 삽입/삭제
	// - 임의 접근

	// 반복자(Iterator) : 포인터와 유사한 개념. 컨테이너의 원소(데이터)를 가리키고, 다음/이전 원소로 이동 가능


	vector<int> v(10);

	v.reserve(1000);

	for (vector<int>::size_type i = 0; i < v.size(); i++)
		v[i] = i;

	//vector<int>::iterator it;

	//int* ptr;
	//
	//it = v.begin();
	//ptr = &v[0];

	//cout << (*it) << endl;
	//cout << (*ptr) << endl;

	vector<int>::iterator itBegin = v.begin();
	vector<int>::iterator itEnd = v.end();

	// 참고로, ++it가 it++ 보다 미세하고 성능이 더 좋다. 그 이유는 iterator를 f12눌러서 확인해보면, 연산자 오버로딩할 때
	// it++은 복사하는 작업이 하나 더 추가되기 때문이다.

	// 더 복잡해보이는데? 이걸 왜 쓰는거야
	// iterator는 vector 뿐만 아니라 다른 컨테이너에도 공통적으로 있는 개념
	// STL 한정에서는 다른 컨테이너에서 보편적으로 쓰이기 때문에 통일성을 가질 수 있다.
	// 다른 컨테이너는 v[i]와 같은 인덱스 접근이 안될 수도 있다
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		cout << (*it) << endl;
	}
	
	int* ptrBegin = &v[0];  // v.begin()._Ptr;
	int* ptrEnd = ptrBegin + 10;  // v.end()._PTr;
	for (int* ptr = ptrBegin; ptr != ptrEnd; ++ptr)
	{
		cout << (*ptr) << endl;
	}

	// const int*;
	//vector<int>::const_iterator cit1 = v.cbegin();

	// 이건 뭐 거의 쓸 일 없음
	for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
	{
		cout << (*it) << endl;   // 9 8 7 .... 0
	}
	
	// - 중간 삽입/ 삭제 (BAD)
	// - 처음/끝 삽입/삭제 (BAD / GOOD)
	// - 임의 접근 (Random Access)

	// C++의 기본기 부분. 아주아주 기본기

	// vector = 동적 배열 = 동적으로 커지는 배열 = 배열
	// 원소가 하나의 메모리 블록에 연속하게 저장된다 !!!

	// 데이터를 줭간에 삽입 한다면..?
	// [                            ]
	// [0] [1] [2] [3] [4] [ ]  [ ] 

	v.push_back(1);
	v.pop_back();

	// 3번째 데이터는 어디 있습니까?
	//v[2] = 3;

	vector<int>::iterator insertIt = v.insert(v.begin() + 2, 5);
	vector<int>::iterator eraseIt1 = v.erase(v.begin() + 2);
	vector<int>::iterator eraseIt2 = v.erase(v.begin() + 2, v.begin() + 4);

	// 쭉 ~ 스캔을 하면서, 3이라는 데이터가 있으면 일괄 삭제하고 싶다
	for (vector<int>::iterator it = v.begin(); it != v.end(); )
	{
		int data = *it;
		if (data == 3)
		{
			// v.erase(it); // 이렇게 하면 컨테이너에 소속된 이터레이터 자체가 삭제되어버려서 이후 반복에서 더는 활용할 수 없음
			it = v.erase(it);
		}
		else
		{
			++it;
		}
	}
	
	return 0;

}