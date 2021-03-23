#include <iostream>
using namespace std;

// 오늘의 주제 : 은닉성

// 객체지향 (OOP Object Oriented Programming)
// - 상속성
// - 은닉성
// - 다형성
// 

// 다형성(Polymorphism = Poly  + morph) = 겉은 똑같은데, 기능이 다르게 동작한다
// - 오버로딩(overloading) = 함수 중복 정의 = 함수 이름의 재사용
// - 오버라이딩(overriding) = 재정의 = 부모 클래스의 함수를 자식 클래스에서 재정의

// 바인딩(Binding) = 묶는다
// - 정적 바인딩(Static Binding) : 컴파일 시점에 결정
// - 동적 바인딩(Dynamic Binding) : 실행 시점에 결정 -> 면접 단골 질문

// 일반 함수는 정적 바인딩 사용
// 동적 바인딩을 원한다면? ->  가상 함수 (virtual function) 활용

class Player
{
public:
	void Move() { cout << "Move Player !" << endl; }
	//void Move(int a) { cout << "Move Player (int) !" << endl; }
	virtual void VMove() { cout << "Move Player !" << endl; }    // 동적 바인딩 사용

public:
	int _hp;
};

class Knight : public Player
{
public:
	void Move() { cout << "Knight Player !" << endl; }

	// 가상 함수는 재정의를 하더라도 가상 함수다!
	// 재정의할 때 virtual을 없애도 virtual이 자동으로 붙게된다.
	virtual void VMove() { cout << "Move Knight !" << endl; }

public:

	int _stamina;
};

class Mage : public Player
{
public:
	int _mana;
};

// 플레이어는 기사다? No
// 기사는 플레이어다? Yes

// [ [ Player ] ]
// [   Knight   ]

void MovePlayer(Player* player)
{
	player->VMove();
}

void MoveKnight(Knight* knight)
{
	knight->Move();
}

int main()
{
	Knight k;
	Player p;
	// MovePlayer(&p)  -> 가능
	// MovePlayer(&k) -> 가능
	// MoveKnight(&p); // ->불가능
	// MoveKnight(&k); // -> 가능

	MovePlayer(&p);
	MovePlayer(&k);

	return 0;
}