#pragma once

//#include "Monster.h"

// class�� ���赵
class Player
{

public:

	void KillMonster();

	void KillMonster2()
	{
		_target2->_hp = 0;  // ��Ÿ�� ���� �߻�, ���赵�� ���λ����� �𸣴ϱ�!
		// ������ �� �κ��� monster.h�� include �� cpp���Ͽ��� �����ϰ� �����ϸ� ������ �߻����� �ʴ´�. ��? ���赵�� �ƴϱ� 
	}

public:
	int _hp;
	int _attack;

	class Monster* _target2;
	//Player* _target;   // �����͸� ����ϸ� �̰͵� ������ 
};

