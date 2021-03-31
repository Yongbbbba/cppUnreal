#include <iostream>
#include <vector>

using namespace std;

// 오늘의 주제 : vector
// STL (Standard Template Library)
// 프로그래밍할 때 필요한 자료구조/알고리즘들을
// 템플릿으로 제공하는 라이브러리

// 컨테이너(Container) : 데이터를 저장하는 객체 (자료구조 Data Structure, 데이터를 어떤 식을 저장할 것인가?) 

// vector (동적 배열)
// - vector의 동작 원리 (size/capacity)
// - 중간 삽입/ 삭제 
// - 처음/끝 삽입/삭제
// - 임의 접근

// 동적 배열
// 매우 매우 중요한 개념 -> 어떤 마법을 부렸길래 배열을 '유동적으로' 사용한 것인가?

// 1) (여유분을 두고) 메모리를 할당한다
// 2) 여유분까지 꽉 찼으면, 메모리를 증설한다

// Q1) 여유분은 얼만큼이 적당할까? 
// Q2) 증설을 얼만큼 해야할까?
// Q3) 기존의 데이터를 어떻게 처리할까?


int main()
{	
	// 배열
	const int MAX_SIZE = 10;
	int arr[MAX_SIZE] = {};

	for (int i = 0; i < MAX_SIZE; i++)
		arr[i] = i;
	for (int i = 0; i < MAX_SIZE; i++)
		cout << arr[i] << endl;
	// 여기서 중간에 또는 추가로 데이터를 넣고 싶을 때는 어떻게 해야하는가? - 기본 정적 배열의 단점

	// 동적 배열

	vector<int> v;
	// size (실제 사용 데이터 개수)
	// capacity (여유분을 포함한 용량 개수)
	// 컴파일러에 따라 여유분을 확보하는 정도가 다르다
	// 이렇게 하는 이유가 뭘까?
	// vector도 선형 자료구조이기 때문에 capa를 늘리기 위해서는 새로운 공간을 확보해야한다. 이런 이사비용이 존재하기 때문에 딱 맞춰서 늘리는게 아니라 여유분을 확보한다
	// v.reserve(1000); // 수동으로 공간을 확보하는 방법

	for (int i = 0; i < 1000; i++)
	{
		v.push_back(100);
		cout << v.size() << " " << v.capacity() << endl;
	}

	//v.push_back(1);
	//v.push_back(2);
	//v.push_back(3);
	//v.push_back(4);
	//v.push_back(5);

	//const int size = v.size();

	//for (int i = 0; i < size; i++)
	//{
	//	cout << v[i] << endl;
	//}

	return 0;

}