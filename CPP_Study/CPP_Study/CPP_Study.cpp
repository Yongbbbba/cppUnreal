#include <iostream>

using namespace std;

// 오늘의 주제 : 함수 포인터	


int Test(int a, int b)
{
	cout << "Test" << endl;

	return 0;
}

class Knight
{
public:

	// 정적 함수
	// 객체와 관련은 없음
	static void HelloKnight()
	{

	}

	// 멤버 함수 
	int GetHp(int, int)
	{
		cout << "GetHp()" << endl;
		return _hp;
	}
public:
	int _hp;
};


// typedef의 진실
// typedef 왼쪽 오른쪽값 -> 오른쪽 (커스텀 타입 정의)

// 정확히는 왼쪽/오른쪽 기준이 아니라,
// [선언 문법]에서 typedef을 앞에다 붙이는 쪽

typedef int INTEGER;
typedef int* POINTER;
typedef int FUNC(int, int);
typedef int ARRAY[20];

typedef int(*PFUNC)(int, int); // 함수 포인터 
typedef int(Knight::*PMEMFUNC)(int, int);  // 멤버 함수 포인터 


int main()
{	

	// 함수 포인터 구성 요소
	// 1) 포인터		*
	// 2) 변수 이름     fn
	// 3) 데이터 타입	함수(인자로 int 2개를 받고, int 1개를 반환)

	FUNC t;  // 일반적인 변수의 선언처럼 메모리에 올라가는 개념이 아님. 


	int(*fn)(int, int);  // 함수 포인터 만들기

	//typedef int(FUNC_TYPE)(int, int);
	// using FUNC_TYPE =  int(*)(int, int);

	//FUNC_TYPE* fn;

	fn = Test;
	// fn = &Test;   //  & 생략 가능 (C언어 와의 호환성 때문)

	fn(1, 2);

	(*fn)(1, 2);

	// 위 문법으로 [전역 함수 / 정적 함수/만 담을 수 있다 (호출 규약이 동일한 애들)
	//fn = &Knight::GetHp;
	
	Knight k1;
	k1.GetHp(1, 1);

	PMEMFUNC mfn;

	mfn = &Knight::GetHp;  // 멤버 함수에는 & 반드시 붙여야함
	
	(k1.*mfn)(1, 2);

	Knight* k2 = new Knight();
	((*k2).*mfn)(1, 1);
	(k2->*mfn)(1, 1);   // 실무에서 잘 사용 안하는 문법이긴 함.. 서버 시간에 사용하기는 것

	delete k2;

	return 0; 
}