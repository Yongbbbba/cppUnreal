#include <iostream>

using namespace std;

// 오늘의 주제 : 템플릿 기초
// 템플릿 가지고만 책을 한 권 쓸 수 있을 정도로 중요하고 방대한 개념이다.
// 여기서는 STL을 사용하기 전에 개념을 이해햐기 위한 정도로 템플릿을 학습하고
// 추후 고급 C++ 강의에서 템플릿을 다시 다루도록 ... 

class Knight
{
public:
	
public:
	int _hp = 100;
};

// 컴파일 단계에서 각기 다른 버전의 Print를 만들어낸다
template<typename T>
void Print(T a)
{
	cout << a << endl;
}

// 템플릿 특수화
template<>
void Print(Knight a)
{
	cout << "Knight !!!!!" << endl;
	cout << a._hp << endl;
}

template<typename T>
T Add(T a, T b)
{
	return a + b;
}

template<typename T1, typename T2>
void Print(T1 a, T2 b)
{
	cout << a << " " << b << endl;
}

//  연산자 오버로딩 (전역함수 버전)
ostream& operator<<(ostream& os, const Knight& k)
{
	os << k._hp;
	return os;
}



int main()
{	
	// 템플릿 : 함수나 클래스를 찍어내는 틀 
	// 1) 함수 템플릿
	// 2) 클래스 템플릿

	Print<int>(50);  // 이렇게 명시적으로 표현할 수도 있다 
	Print(50.0f);
	Print(50.0);

	Print("Hello", 100);

	int result1 = Add(1, 2);
	float result2 = Add<float>(0.1f, 0.2f);

	cout << result1 << " " << result2 << endl;

	Knight k1;
	Print(k1);

	return 0; 
}