#include <iostream>
#include <vector>

using namespace std;

// 오늘의 주제 : 중괄호 초기화 { }	

class Knight
{
public:
	Knight()
	{

	}
	~Knight()
	{

	}
	Knight(initializer_list<int> li)
	{
		cout << "Knight(initailizer_list)" << endl;
	}
};
int main()
{	
	// 중괄호 초기화 
	int a = 0;
	int b(0);
	int c{ 0 };

	Knight k1;
	Knight k2 = k1;   // 복사 생성자 호출 (대입 연산자가 아님)
	// Knight k2; // 기본 생성자 호출
	// k2 = k1;  // 이 경우가 대입 연산자 사용

	Knight k3{ k1 };  

	int arr[] = { 1,2,3,4 };

	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);

	vector<int> v2(10, 1);


	// 중괄호 초기화 
	// 1) vector 등 container와 잘 어울린다
	vector<int> v3{ 1,2,3,4 };
	// 2) 축소 변환 방지
	int x = 0;
	double y = x; // 가능한
	// double z{ x };  // 축소 변환 방지해서 빌드가 안됨

	// 3) Bonus
	Knight k4(); // 이게 기본생성자 호출하라는 의미가 아님, 함수를 선언해준 것과 모양이 같음
	Knight k5{}; // 중괄호를 사용하면 기본생성자 호출을 하게 해줌

	Knight k5{ 1,2,3,4,5 };

	// 취향 차이임
	// 
	// 괄호 초기화 ()를 기본으로 간다
	// - 전통적인 C++ (거부감이 없음)
	// - vector 등 특이한 케이스에 대해서만 {} 사용

	// 중괄호 초기화 {}를 기본으로 간다
	// - 초기화 문법의 일치화
	// - 축소 변환 방지


	return 0; 
}