#include <iostream>
#include <string>

using namespace std;

// 오늘의 주제 : 함수 마무리
// 오버로딩 (중복 정의 : 함수 이름의 재사용)
// - 매개변수 갯수가 다르거나 
// - 매개변수 타입이 다르거나 (순서가 다른걸 포함)


int Add(int a, int b)
{
	return a + b;
}
float Add(float a, float b)
{
	return a + b;
}

// 기본 인자값 
void SetPlayerInfo(int hp, int mp, int attack, int guildId=0)
{
	return;
}

// 스택 오버플로우
int factorial(int n)
{
	if (n <= 1)
		return 1;

	return n * factorial(n - 1);
}
int main()
{
	cout << factorial(10);
	// cout << factorial(100000); // 스택 오버플로우

	return 0;

}

