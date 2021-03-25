#include <iostream>
using namespace std;

// 오늘의 주제 : 얕은 복사  vs 깊은 복사
// 면접 단골 질문
class Pet
{
public:
	Pet()
	{
		cout << "Pet()" << endl;
	}
	~Pet()
	{
		cout << "~Pet()" << endl;
	}
	Pet(const Pet& pet)
	{
		cout << "Pet(const Pet&)" << endl;
	}

	Pet& operator=(const Pet& pet)
	{
		cout << "operator=(const pet&)" << endl;
		return *this;
	}
};

class Player
{
public:
	Player()
	{
		cout << "Player()" << endl;
	}

	// 복사 생성자
	Player(const Player& player)
	{
		cout << "Player(const Player&)" << endl;
		_level = player._level;
	}

	// 복사 대입 연산자
	Player& operator=(const Player& player)
	{
		cout << "operator=(const Player&)" << endl;
		_level = player._level;
		return *this;
	}

public:
	int _level = 0;
};

class Knight : public Player
{
public:
	Knight()
	{
	
	}

	Knight(const Knight& knight) : Player(knight), _pet(knight._pet)  // 이렇게 안하면 기본 생성자 호출됨
	{
		cout << "Knight(const Knight&)" << endl;

		_hp = knight._hp;
	}

	~Knight()
	{
	}

public:
	int _hp = 100;
	
	Pet _pet;
};


int main()
{
	Knight knight; // 기본 생성자
	knight._hp = 200;
	knight._level = 99;

	cout << "---------------복사 생성자----------------" << endl;
	Knight knight2 = knight;  // 복사 생성자

	cout << "---------------복사 대입 연산자----------------" << endl;
	Knight knight3;  // 기본 생성자
	knight3 = knight; // 복사 대입 연산자
	
	// 실험)
	// - 암시적 복사 생성자 Steps
	// 	   1) 부모 클래스의 복사 생성자 호출
	// 	   2) 멤버 클래스의 복사 생성자 호출 (멤버 변수에 클래스 타입의 변수가 있을 경우)
	// 	   3) 멤버가 기본 타입일 경우 메모리 복사 (얕은 복사 방식) 
	// 
	// - 명시적 복사 생성자 Steps
	// 1) 부모 클래스의 기본 생성자 호출
	// 2) 멤버 클래스의 기본 생성자 호출

	// - 암시적 복사 대입 연산자 Steps
	// 	   1) 부모 클래스의 복사 대입 연산자 호출
	// 	   2) 멤버 클래스의 복사 대입 연산자 호출 (멤버 변수에 클래스 타입의 변수가 있을 경우)
	// 	   3) 멤버가 기본 타입일 경우 메모리 복사 (얕은 복사 방식) 
	// - 명시적 복사 대입 연산자 Steps
	// 1) 알아서 해주는거 없음

	// 왜 이렇게 혼란스러울까?
	// 객체를 '복사'한다는 것은 두 객체의 값들을 일치시키려는 것
	// 따라서 기본적으로 얕은 복사 (Shallow Copy) 방식으로 동작한다.

	// 명시적 복사 -> [모든 책임]을 프로그래머한테 위임하겠다는 의미

	// 우리가 커스터마이징해서 깊은 복사를 구현하려고 한다면.. 기본적으로 처리되는 부분들이 누락되기 때문에
	// 이것들을 제대로 챙겨주지 않으면 반쪽자리 복사가 되게 된다.

	return 0;
}