#include <iostream>
#include <string>

using namespace std;

// 오늘의 주제 : 호출 스택
void Func1();
void Func2(int hp, int mp);
void Func3(float); // 이런 식으로 함수원형을 선언할 때는 매개변수 이름을 적어두지 않을 수는 있지만, 프로그램 규모가 커진다면 파라미터명을 넣는 것을 권장

void Func1()
{
	cout << "Func1" << endl;

	Func2(1, 2);
}

void Func2(int hp, int mp)
{
	cout << "Func2" << endl;

	Func3(0.1f);
}

void Func3(float a)
{
	cout << "Func3" << endl;
}

int main()
{
	cout << "main()" << endl;
	Func1();

}

