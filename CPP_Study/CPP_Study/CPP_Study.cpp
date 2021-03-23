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

// 복사 대입 연산자
// - 대입 연산자가 나온 김에 [복사 대입 연산자]에 대해 알아보자
// 용어가 좀 헷갈린다 [복사 생성자] [대입 연산자] [복사 대입 연산자] @_@
// - 복사 대입 연산자 = 대입 연산자 중, 자기 자신의 참조 타입을 인자로 받는 것

// 기타
// - 모든 연산자를 다 오버로딩 할 수 있는 것은 아니다 (:: . .* 이런건 안됨)
// - 모든 연산자가 다 2개 항이 있는 것은 아님. ++ --가 대표적 (단항 연산자)
// - 증감 연산자 ++ --
// -- 전위형 (++a) operator++()
// -- 후위형 (a++) operator++(int)

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

	Position& operator=(int arg)
	{
		_x = arg;
		_y = arg;

		return *this;  // this는 자기 자신을 가리키고 있는 포인터
	}

	// 복사 대입 연산자
	// [복사 생성자] [복사 대입 연산자] 등 복사 시리즈가 특별 대우를 받는 이유는,
	// 말 그대로 객체가 '복사'되길 원하는 특징 때문
	// TODO ) 동적 할당 시간에 더 자세히 알아볼 것

	Position& operator=(const Position& arg)
	{
		_x = arg._x;
		_y = arg._y;

		return *this;  
	}

	Position& operator++()
	{
		_x++;
		_y++;

		return *this;
	}


	Position operator++(int)
	{
		Position ret = *this;
		_x++;
		_y++;
		return ret;
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