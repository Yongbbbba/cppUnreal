#include "Knight.h"
#include <iostream>

Knight::Knight() 
{

}

Knight::Knight(int hp) : Player(hp)
{

}

Knight::~Knight()
{
	std::cout << "~Knight()" << std::endl;
}

