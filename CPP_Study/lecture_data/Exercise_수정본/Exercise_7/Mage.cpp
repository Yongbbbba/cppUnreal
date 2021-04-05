#include "Mage.h"
#include <iostream>

Mage::Mage()
{

}

Mage::Mage(int hp) : Player(hp)
{

}

Mage::~Mage()
{
	std::cout << "~Mage()" << std::endl;
}

