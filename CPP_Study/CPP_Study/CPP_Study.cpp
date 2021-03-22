#include <iostream>
using namespace std;

// 오늘의 주제 : 상속성

// 객체지향 (OOP Object Oriented Programming)
// - 상속성
// - 은닉성
// - 다형성
// 
// 
// class는 일종의 설계도

// 메모리
// [ [ Player ] ]
// [    Knight   ]

// 상속(Inheritance) 부모 -> 자식에게 유산을 물려주는 것

// 생성자(N) /소멸자(1)

// 생성자는 탄생을 기념해서 호출되는 함수? 
// - Knight를 생성하면 -> Player의 생성자? Knight의 생성자?
// -> 솔로몬의 선택 ! 그냥 둘다 호출하자! 

// RPG 게임에서 최상위 객체를 만들어주면서 시작
// GameObject
// - Creature
// -- Player, Monster, Mpc, Pet
// - Projectile
// -- Arrow, Fireball
// - Env

// Item
// - weapon
// -- Swrod, Bow
// - Armor
// -- Helmet. Boots

class Player
{
public:

	Player()
	{
		_hp = 0;
		_attack = 0;
		_defence = 0;
		cout << "Player() 기본 생성자 호출" << endl;
	}

	Player(int hp)
	{
		_hp = hp;
		_attack = 0;
		_defence = 0;
		cout << "Player(int) 기타 생성자 호출" << endl;
	}

	~Player()
	{
		cout << "~Player() 소멸자 호출" << endl;
	}


	void Move() { cout << "Player Move 호출" << endl; }
	void Attack() { cout << "Player Attack 호출" << endl; }
	void Die() { cout << "Player Die 호출" << endl; }

public:
	int _hp;
	int _attack;
	int _defence;
};

class Knight : public Player
{
public:
	Knight()
	{
		/*
			선(먼저)처리 영역
			- 여기서 Player() 생성자 호출
		*/

		_stamina = 100;
		cout << "Knight() 기본 생성자 호출" << endl;

	}

	Knight(int stamina) : Player(100)  // 선처리 영역의 생성자를 지정할 수 있다.
	{
		cout << "Knight(int) 기타 생성자 호출" << endl;
		_stamina = stamina;
	}

	~Knight()
	{
		cout << "~Knight() 소멸자 호출" << endl;

		/*
			일종의 후(나중에)처리 영역이 존재
			- 여기서 ~Player() 소멸자를 호출
		*/
	}

	// 재정의: 부모님의 유산을 거부하고 새로운 이름으로 만든?
	void Move() { cout << "Knight Move 호출" << endl; }
public:
	int _stamina;
};

class Mage : public Player
{
public:

public:
	int _mp;
};

int main()
{
	Knight k(100);

	k._hp = 100;
	k._attack = 10;
	k._defence = 5;
	//k._stamina = 50;

	k.Move();
	// k.Player::Move();  // 실무에서 거의 쓸 일이 없음. 이렇게 쓸 일이 있다는 것은 애초에 잘못 만든 것..
	k.Attack();
	k.Die();
	
	return 0;
}  