#pragma once
#include "Player.h"

class Pet;

class Archer : public Player
{
public:
	Archer();
	Archer(int hp);
	virtual ~Archer();

public:
	Pet* _pet;
};

