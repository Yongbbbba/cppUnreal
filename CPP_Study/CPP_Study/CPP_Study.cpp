#include <iostream>
using namespace std;

// 오늘의 주제 : 연산자 오버로딩(Operator Overloading)

// 연산자 vs 함수
// - 연산자는 피연산자의 개수/타입이 고정되어 있음

// 연산자 오버로딩?
// 일단 [연산자 함수]를 정의해야함
// 함수도 멤버함수 vs 전역함수가 존재하는 것처럼, 연산자 함수도 두 가지 방식으로 만들 수 있음

// - 멤버 연산자 함수 version
// -- a op b 형태에서 왼쪽을 기준으로 실행됨 (a가 클래스여야 가능, a를 '기준 피연산자'라고 함)
// -- 한계) a가 클래스가 아니면 사용 못함

// - 전역 연산자 함수 version
// -- a op b 형태라면 a, b 모두를 연산자 함수의 피연산자로 만들어준다

// 그럼 무엇이 더 좋은가? 그런거 없음. 심지어 둘 중 하나만 지원하는 경우도 있기 때문.
// - 대표적으로 대입 연산자 (a = b)는 전역 연산자 version으로는 못 만든다

class Position
{
public:
	Position operator+(const Position& arg)
	{
		Position pos;
		pos._x = _x + arg._x;
		pos._y = _y + arg._y;

		return pos;
	}

	Position operator+(int arg)
	{
		Position pos;
		pos._x = _x + arg;
		pos._y = _y + arg;

		return pos;
	}

	bool operator==(const Position& arg)
	{
		if (_x == arg._x && _y == arg._y)
			return true;
		return false;
	}
	
public:
	int _x;
	int _y;
};


// 클래스 안에서 멤버 연산자 함수를 만든다면 왼쪽이 무조건 클래스 타입이어야 하지만
// 아래 처럼 전역 연산자 함수를 만들면 그것에서 자유로워진다.
Position operator+(int a, const Position & b)
{
	Position ret;

	ret._x = b._x + a;
	ret._y = b._y + a;

	return ret;
}

int main()
{
	Position pos;
	pos._x = 0;
	pos._y = 0;

	Position pos2;
	pos2._x = 1;
	pos2._y = 1;

	// 아래 둘은 같은 의미임
	Position pos3 = pos + pos2;
	pos3 = pos.operator+(pos2);

	// 아래 둘은 같은 의미임
	Position pos4 = pos3 + 1;  //  1 + pos3는 작동하지 않음
	pos4 = pos3.operator+(1);

	bool isSame = (pos3 == pos4);
	
	return 0;
}