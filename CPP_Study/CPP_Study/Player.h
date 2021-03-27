#pragma once

//#include "Monster.h"

// class는 설계도
class Player
{

public:

	void KillMonster();

	void KillMonster2()
	{
		_target2->_hp = 0;  // 런타임 에러 발생, 설계도의 세부사항을 모르니까!
		// 하지만 이 부분을 monster.h가 include 된 cpp파일에서 동일하게 구현하면 에러가 발생하지 않는다. 왜? 설계도를 아니까 
	}

public:
	int _hp;
	int _attack;

	class Monster* _target2;
	//Player* _target;   // 포인터를 사용하면 이것도 가능함 
};

