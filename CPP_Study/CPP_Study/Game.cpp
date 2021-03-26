#include "Game.h"
#include "Player.h"
#include <iostream>

using namespace std;

Game::Game() : _player(nullptr)
{

}

Game::~Game()
{

}

void Game::Init()
{

}

void Game::Update()
{
	if (_player == nullptr)
		CreatePlayer();
}

void Game::CreatePlayer()
{
	while (_player == nullptr)
	{
		cout << "----------------------" << endl;
		cout << "ĳ���͸� �����ϼ���!" << endl;
		cout << "1) ��� 2) �ü� 3) ����" << endl;
		cout << "----------------------" << endl;

		cout << "> ";
		
		int input = 0;	
		cin >> input;

		switch (input)
		{
		case PT_Knight:
			_player = new Knight();
			break;
		case PT_Archer:
			_player = new Archer();
			break;
		case PT_Mage:
			_player = new Mage();
			break;
		}
	}
}