#pragma once
#include "Creature.h"

// 일반적으로 헤더파일에는 선언만 해놓고 
// cpp 파일에 구현한다. 하지만 구현이 간략한 경우에는 헤더파일에 하기도 한다.
// 근데 이거는 회사마다 규칙에 따르면 될듯

enum PlayerType
{
	PT_Knight = 1,
	PT_Archer = 2,
	PT_Mage = 3,
};

class Player : public Creature
{
public:
	Player(int playerType) : Creature(CT_PLAYER), _playerType(playerType)
	{

	}

	// 왜 소멸자를 가상함수로 만드는지는 이전 강의 참고
	virtual ~Player()
	{

	}
protected:
	int _playerType;
};

class Knight : public Player
{
public:
	Knight() : Player(PT_Knight)
	{
		_hp = 150;
		_attack = 10;
		_defence = 5;
	}
};

class Archer : public Player
{
public:
	Archer() : Player(PT_Archer)
	{
		_hp = 80;
		_attack = 15;
		_defence = 3;
	}
};

class Mage : public Player
{
public:
	Mage() : Player(PT_Mage)
	{
		_hp = 50;
		_attack = 25;
		_defence = 3;
	}
};
