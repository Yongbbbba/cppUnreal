#include "Player.h"
#include "Monster.h"

void Player::KillMonster()
{
	_target2->_hp = 0;

	// [ аж╪р ]  -> [ [ monsterId (4)] [ hp(4) ] [ defence(4) ] ]
	// (*target2)._hp = 0;
}